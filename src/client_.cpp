#include <iostream>
#include <string>
#include <memory>
#include <functional>


#include "definitions.h"
#include "Client.h"
#include "CommunicationChannel.h"

void requestCycle(std::shared_ptr<net::Client> client, std::string response) 
{
    std::cout << "Server response: " << response << std::endl;
    std::cout << "Enter your request: ";
    std::string request;
    std::getline(std::cin, request);
    client->request(request, std::bind(
        requestCycle,
        client,
        std::placeholders::_1
    ));
}

int main() {
    unsigned short  port = 3333;
    std::string address  = "127.0.0.1";
    auto ip = net::ip_address::from_string(address);
    net::endpoint ep(ip, port);
    net::io_service ios;
    net::io_service::work work(ios);

    std::shared_ptr<net::Client> client(new net::Client(ios, ep));

    client->onConnected([&client]() {
        client->request(
           "hello", 
           std::bind(
                requestCycle,
                client,
                std::placeholders::_1
            )
        );
    });

    client->connect();


    ios.run();


    return 0;
}