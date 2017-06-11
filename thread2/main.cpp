#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <future>

//int factorial(int N)
//{
//    int res = 1;
//    for(int i = N; i >1; i--)
//    {
//        res *= i;
//    }

//    std::cout << "Result is: " << res << std::endl;

//    return res;
//}

class A{
public:
    void f(int x, char c) {}
    int operator ()(int N){return 0;}
};

int factorial(std::future<int> &f)
{
    int res = 1;
    int N = f.get();
    for(int i = N; i >1; i--)
    {
        res *= i;
    }

    std::cout << "Result is: " << res << std::endl;

    return res;
}

void foo(int x ){}

int main()
{
    int x;
    std::promise<int> p;
    std::future<int>fu2 = p.get_future();
//    std::thread t1(factorial, 10, std::ref(x));
//    t1.join();
    //std::future<int> fu = std::async(std::launch, factorial, 10); //不创建子进程，延时调用get函数
    //std::future<int> fu = std::async(std::launch::async, factorial, 10);
    std::future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial, std::ref(fu2)); //std::launch::deferred默认函数
    p.set_value(4);
    x = fu.get();
    std::cout << "Res: " << x << std::endl;
//   多线程调用方式
//    A a;
//    std::thread th1(a, 6); //传递a的拷贝个子线程
//    std::thread th2(std::ref(a), 6); //传递a的引用个子线程
//    std::thread th3(std::move(a), a);//a在主线程中不再生效
//    std::thread th4(A(), 6); //传递临时创建的a对象个子线程

//    std::thread th5(foo, 6);
//    std::thread th6([](int x){return x*x}, 6);

//    std::thread th7(&A::f, a, 8, 'w'); //传递a的拷贝的成员函数给子线程
//    std::thread th8(&A::f, &a, 8, 'w'); //传递a的地址的成员函数个子线程

//    std::async(std::launch, a, 6);
    return 0;
}
