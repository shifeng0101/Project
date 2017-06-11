#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define closesocket close
#endif

#include <string.h>
#include <stdlib.h>
#include <thread>
#include <iostream>



    void Main(int client)
    {
        std::cout << "Start Main..." << std::endl;
        char buf[1024] = {0};
        while(1)
        {
            int leng = recv(client, buf, sizeof(buf)-1, 0);
            if(0 >= leng) break;
            if(NULL != strstr(buf, "quit"))
            {
                char re[] = "Quit success!\n";
               send(client, &re, strlen(re) +1, 0);
                break;
            }
            send(client, "Ok\n", 4, 0);

            std::cout << "recv: " << buf << std::endl;
        }

        std::cout << "End Main ...." << std::endl;

        closesocket(client);
    }




int main(int argc, char *argv[])
{
#ifdef WIN32
    WSADATA ws;
    WSAStartup(MAKEWORD(2,2), &ws);
#endif

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sock)
    {
        std::cout << "Create socket failed!\n";
        return -1;
    }
    std::cout << "socked id: " << sock << std::endl;

    unsigned short port = 8083;
    if(1 < argc )
    {
        port = atoi(argv[1]);

    }
    sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(0);

    if(::bind(sock, (sockaddr*) &saddr, sizeof(saddr)))
    {
        std::cout << "Bind port %d failed!\n" << port << std::endl;
        return -2;
    }
    std::cout << "Bind port %d success !\n" << port << std::endl;

    listen(sock, 10);

    while(1)
    {
        sockaddr_in caddr;
        socklen_t len = sizeof(caddr);

        int client = accept(sock, (sockaddr*)&caddr,&len);
        if(0 >= client ) break;
        std::cout  << "Accept Client %d" << client << std::endl;
        char *ip = inet_ntoa(caddr.sin_addr);
        unsigned short cport = ntohs(caddr.sin_port);

        std::cout << "Client IP: %s" << ip <<"  port: " << cport << std::endl;

        std::thread t1(Main, client);
        t1.detach();

    }
    closesocket(sock);
    return 0;
}
