#include "MsgHandler.hpp"

MsgHandler::MsgHandler(std::shared_ptr<ServiceManagerAdapter> servManger, std::shared_ptr<std::vector<uint16_t>> events)
    : serviceManager{servManger},
      msgHandlerEvents{events}
{
}

void MsgHandler::Serialize()
{
    if (msgHandlerEvents->front() == currentEvent)
    {
        serializedMsg.resize(sizeof(msg_DSRC));
        memcpy(serializedMsg.data(), &msgDRC, sizeof(msg_DSRC));
    }
    else
    {
        serializedMsg.resize(sizeof(msg_diagnostic));
        memcpy(serializedMsg.data(), &msgDiagnostic, sizeof(msg_diagnostic));
    }
}

void MsgHandler::HandleMsg(const boost::asio::ip::udp::endpoint &endpoint, const std::string &data)
{
    switch (endpoint.port())
    {
    case SRC_PORTS::HEADING_PORT:
        msgDRC.heading = stoi(data);
        currentEvent = msgHandlerEvents->front();
        break;
    case SRC_PORTS::SPEED_PORT:
        msgDRC.speed = stoi(data);
        currentEvent = msgHandlerEvents->front();
        break;
    case SRC_PORTS::TYRES_PORT:
        msgDiagnostic.tyres = (TYRES)stoi(data);
        currentEvent = msgHandlerEvents->back();
        break;
    case SRC_PORTS::BATTERY_PORT:
        msgDiagnostic.battery = (BATTERY)stoi(data);
        currentEvent = msgHandlerEvents->back();
        break;
    case SRC_PORTS::HEAD_LIGHT_PORT:
        msgDiagnostic.headLight = (HEAD_LIGHT)stoi(data);
        currentEvent = msgHandlerEvents->back();
        break;
    default:
        msgDiagnostic.oilLevel = (OIL_LEVEL)stoi(data);
        currentEvent = msgHandlerEvents->back();
    }
    Serialize();
    serviceManager->updateEvent(currentEvent, serializedMsg);
    std::cout << "updated event\n";
}