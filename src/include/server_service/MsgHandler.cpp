#include "MsgHandler.hpp"
#include <json.hpp>

#define HEAD_COUNTER 20

int head_counter = HEAD_COUNTER;

MsgHandler::MsgHandler(std::shared_ptr<ServiceManagerAdapter> servManger)
    : serviceManager{servManger}
{
}

void MsgHandler::HandleMsg(const boost::asio::ip::udp::endpoint &endpoint, const std::string &data)
{
    using json = nlohmann::json;
    json jsonMessage = {
        {"route", "alerts/receive"},
        {"code", ""},
        {"state", ""},
        {"description", ""},
    };
    try
    {
        jsonMessage["state"] =
            (std::stoi(data) == (uint8_t)DIAG_STATE::OKAY) ? "OKAY" : "FAULTY";
    }
    catch (const std::invalid_argument &ia)
    {
        std::cerr << "Invalid argument: " << ia.what() << std::endl;
        return;
    }

    catch (const std::out_of_range &oor)
    {
        std::cerr << "Out of Range error: " << oor.what() << std::endl;
        return;
    }

    catch (const std::exception &e)
    {
        std::cerr << "Undefined error: " << e.what() << std::endl;
        return;
    }

    switch (endpoint.port())
    {
    case (int)SRC_PORTS::SPEED_PORT:
        currentEvent = SPEED_EVENT_ID;
        msgType = MSG_TYPE::DSRC;
        break;
    case (int)SRC_PORTS::HEADING_PORT:
        if (head_counter == 0)
        {
            head_counter = 100;
            currentEvent = HEADING_EVENT_ID;
            msgType = MSG_TYPE::DSRC;
            head_counter = HEAD_COUNTER;
            break;
        }
        else{
            head_counter--;
            return;
        }
    case (int)SRC_PORTS::TYRES_PORT:
        jsonMessage["code"] = "C1234";
        jsonMessage["description"] = "Tyre pressure";
        msgType = MSG_TYPE::DIAGNOSTIC;
        break;
    case (int)SRC_PORTS::BATTERY_PORT:
        jsonMessage["code"] = "P0562";
        jsonMessage["description"] = "Main 12v battery";
        msgType = MSG_TYPE::DIAGNOSTIC;
        break;
    case (int)SRC_PORTS::HEAD_LIGHT_PORT:
        jsonMessage["code"] = "B2425";
        jsonMessage["description"] = "Head lights";
        msgType = MSG_TYPE::DIAGNOSTIC;
        break;
    default:
        break;
    }

    if (msgType == MSG_TYPE::DIAGNOSTIC && serviceManager->serviceAvailable.at(REQUEST_SERVICE_ID + REQUEST_INSTANCE_ID))
    {
        std::cout << jsonMessage.dump(4);
        std::string message = jsonMessage.dump(4);
        serviceManager->SendRequest(REQUEST_SERVICE_ID, REQUEST_INSTANCE_ID, REQUEST_METHOD_ID, std::vector<uint8_t>(message.begin(), message.end()));
        std::cout << "request sent!!!\n";
    }
    if (msgType == MSG_TYPE::DSRC)
    {
        std::cout << "updated event!!!\n";
        std::vector<uint8_t> dataToBeSent(data.begin(), data.end());
        serviceManager->updateEvent(currentEvent, dataToBeSent);
    }
}