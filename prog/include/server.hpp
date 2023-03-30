#pragma once
#define SIZE 1024

class Server
{
private:
    /* data */
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket;
    // std::thread thread;
    boost::asio::ip::udp::endpoint sender_endpoint;
    std::vector<char> data;
    // std::vector<std::string> msgs;
    //  std::mutex mtx;
    //    std::thread thread;

public:
    Server(uint16_t port)
        : socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    {
        data.reserve(SIZE);
    }

    ~Server()
    {
        Stop();
    }

    void Start()
    {
        StartRecieve();

        // thread = std::thread(
        //     [this]()
        //     {
        //         while (1)
        //         {
        //             std::scoped_lock lock(mtx);
        //             for (int i = 0; i < msgs.size(); i++)
        //                 std::cout << msgs[i] << '\n';
        //         }
        //     });
        // thread = std::thread(
        //   [this]()
        //{
        std::cout << "Server started!!!" << '\n';
        io_service.run();
        //});
    }

    void Stop()
    {
        io_service.stop();
    }

    void StartRecieve()
    {
        socket.async_receive_from(boost::asio::buffer(data.data(), SIZE), sender_endpoint,
                                  [this](boost::system::error_code ec, std::size_t recvd)
                                  {
                                      if (!ec)
                                      {
                                          //std::cout << "Reading " << recvd << " bytes!\n";
                                          //std::cout << data.size() << '\n';
                                          std::cout << "[" << sender_endpoint << "]: ";
                                          // std::scoped_lock lock(mtx);
                                          for (int i = 0; i < recvd; i++)
                                              std::cout << data[i];
                                          // msgs.push_back(data.data());
                                          // std::cout << data.data();
                                      }
                                      StartRecieve();
                                  });
    }
};
