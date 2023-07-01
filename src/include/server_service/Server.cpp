#include "Server.hpp"

Server::Server(const uint16_t &port, std::shared_ptr<ServiceManagerAdapter> servManager)
    : socket{io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)},
      serviceManager{servManager},
      msgHandler{servManager}
{
}

Server::~Server()
{
    Stop();
}

void Server::Start()
{
    StartRecieve();
    UDP_server_thread = std::move(std::thread([this]()
                                              { io_service.run(); }));
    std::cout << "starting vsomeip\n";
    serviceManager->start();
}

void Server::Stop()
{
    io_service.stop();
}

void Server::StartRecieve()
{
    socket.async_receive_from(boost::asio::buffer(data.data(), SIZE), sender_endpoint,
                              [this](boost::system::error_code ec, std::size_t recvd)
                              {
                                  if (!ec)
                                  {
                                      std::string newStr(data.data(), recvd);
                                      std::cout << "[" << sender_endpoint << "]: ";
                                      std::cout << newStr << '\n';
                                      msgHandler.HandleMsg(sender_endpoint, newStr);
                                  }
                                  StartRecieve();
                              });
}
