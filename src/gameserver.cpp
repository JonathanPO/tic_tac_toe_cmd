#include <iostream>
#include <string>

#include "definitions.h"
#include "Server.h"
#include "Connection.h"
#include "game.h"
#include <memory>
#include <boost/algorithm/string.hpp>
#include <vector>

int main() {
    unsigned short  port = 3333;
    auto ip              = net::ip_address_v4::any();

    net::endpoint ep(ip, port);
    net::io_service ios;
    net::io_service::work work(ios);

    std::shared_ptr<net::Server> server(new net::Server(ios, ep));

    server->onMessage([](net::CommunicationChannel& channel, std::string request) {
        vector<string> mySplited; 

        split(mySplited,request,is_any_of("|"));

        if (request == "init") {
            channel.write("----------JOGO COMEÇOU----------");
        }

        if(mySplited[0] == "play"){
            i = std::stoi(mySplited[1]);
            j = std::stoi(mySplited[2]);

            if(game->play(i, j)){
                channel.write("valid");
            } else{
                channel.write("invalid");
            }
        }

        if(request == "board"){
            channel.write(game->showBoard());
        }

        if(request == "anyWin"){
            if(game->testWin()){
                channel.write("anyWin");
            } else{
                channel.write("noWin");
            }
        }
        

        if(request == "changeTurn"){
            if(game->changeTurn()){
                channel.write("X");
            } else{
                channel.write("O");
            }
        }

        if(request == "draw"){
            if(game->getDraw()){
                channel.write("draw");
            } else{
                channel.write("not draw");
            }
        }

        if(request == "winner"){
            if(game->getWinner()){
                channel.write("X");
            } else{
                channel.write("O");
            }
        }

    });

    server->start();
    ios.run();


    return 0;
}
