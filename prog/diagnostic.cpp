#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <server.hpp>
#include <vector>
#define PORT 5001

int main()
{
    Server server(PORT);
    server.Start();
    return 0;
}