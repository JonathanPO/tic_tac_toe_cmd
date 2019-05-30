#include <iostream>
#include <string>

#include "definitions.h"
#include "Server.h"
#include "Connection.h"
#include <memory>

int main() {
    unsigned short  port = 3333;
    auto ip              = net::ip_address_v4::any();

    net::endpoint ep(ip, port);
    net::io_service ios;
    net::io_service::work work(ios);

    std::shared_ptr<net::Server> server(new net::Server(ios, ep));

    server->onMessage([](net::CommunicationChannel& channel, std::string request) {
        if (request == "pontos") {
            //asdfasdf
            channel.write("20");
        } else if (request == "numeroSecreto") {
            channel.write("42");
        } else if (request == "hello") {
            channel.write("Hello from server");
        } else {
            channel.write("Requisição Inválida");
        }
    });

    server->start();
    ios.run();


    return 0;
}
