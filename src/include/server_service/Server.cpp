#include "Server.hpp"

Server::Server(const uint16_t &port, std::shared_ptr<ServiceManagerAdapter> servManager, std::shared_ptr<std::vector<uint16_t>> events)
    : socket{io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)},
      serverEvents{events},
      serviceManager{servManager},
      msgHandler{servManager, events}
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
    for (uint16_t event : *serverEvents)
    {
        serviceManager->addEvent(event);
    }
    serviceManager->offerEvents();
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
                                      std::cout << "[" << sender_endpoint << "]: ";
                                      for (int i = 0; i < recvd; i++)
                                          std::cout << data[i];
                                      msgHandler.HandleMsg(sender_endpoint, data, recvd);
                                  }
                                  StartRecieve();
                              });
}
