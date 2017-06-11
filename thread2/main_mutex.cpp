#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

class LofFile
{
public:
    LofFile()
    {
        f.open("log.txt");
    }

    void shared_print(std::string id, int value)
    {
        std::lock(m_mutex, m_mutex2);
        std::lock_guard<std::mutex> locker(m_mutex, std::adopt_lock);
        std::lock_guard<std::mutex> locker2(m_mutex2, std::adopt_lock);
        f << "From " << id << ": " << value << std::endl;
    }

    void shared_print2(std::string id, int value)
    {
        std::lock(m_mutex, m_mutex2);
        std::lock_guard<std::mutex> locker2(m_mutex2, std::adopt_lock);
        std::lock_guard<std::mutex> locker(m_mutex, std::adopt_lock);

        f << "From " << id << ": " << value << std::endl;
    }

protected:
private:
    std::mutex m_mutex;
    std::mutex m_mutex2;
    std::ofstream f;
};

void function1(LofFile &log)
{
    for(int i =0; i < 100; i++)
    {
        log.shared_print("Hello Sub Thread", i);
    }
}

int main()
{

    LofFile log;
    thread t1(function1, std::ref(log));
    for(int i = 0; i < 100; i++ )
    {
        log.shared_print2("Hello Main Thread", i);
    }
    t1.join();
    return 0;
}

