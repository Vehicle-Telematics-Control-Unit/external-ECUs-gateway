#ifndef __SERVER__
#define __SERVER__

#define SIZE 1024
#include <iostream>
#include <boost/asio.hpp>
#include "MsgHandler.hpp"


class Server
{
private:
    /* data */
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket;
    std::thread UDP_server_thread;
    boost::asio::ip::udp::endpoint sender_endpoint;
    std::string data;
    MsgHandler msgHandler;
    std::shared_ptr<ServiceManagerAdapter> serviceManager;

public:
    Server(const uint16_t &port, std::shared_ptr<ServiceManagerAdapter> servManager);

    ~Server();

    void Start();

    void Stop();

    void StartRecieve();
};

#endif