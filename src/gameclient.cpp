#include <iostream>
#include <string>
#include <memory>
#include <functional>


#include "definitions.h"
#include "Client.h"
#include "CommunicationChannel.h"

bool anyWin = false;
bool valid = false;
bool playerTurn = true;
bool draw = false;
bool winner = true;
std::string player = "X";

void requestInit(std::shared_ptr<net::Client> client, std::string response) 
{
    std::cout << "Game started" << std::endl;
}

void requestBoard(std::shared_ptr<net::Client> client, std::string response) 
{
    std::cout << response << std::endl;
}

void requestPlay(std::shared_ptr<net::Client> client, std::string response) 
{
    if(response == "valid"){
        valid = true;
    } else{
        valid = false;
    }
}

void requestAnyWin(std::shared_ptr<net::Client> client, std::string response) 
{
    if(response == "anyWin"){
        anyWin = true;
    } else{
        anyWin = false;
    }
}

void requestChangeTurn(std::shared_ptr<net::Client> client, std::string response) 
{
    if(response == "X"){
        playerTurn = true;
    } else{
        playerTurn = false;
    }
}

void requestDraw(std::shared_ptr<net::Client> client, std::string response) 
{
    if(response == "draw"){
        draw = true;
    } else{
        draw = false;
    }
}

void requestWinner(std::shared_ptr<net::Client> client, std::string response) 
{
    if(response == "X"){
        winner = true;
    } else{
        winner = false;
    }
}

int main() {
    unsigned short port  = 3333;
    std::string address  = "127.0.0.1";
    auto ip = net::ip_address::from_string(address);
    net::endpoint ep(ip, port);
    net::io_service ios;
    net::io_service::work work(ios);

    std::shared_ptr<net::Client> client(new net::Client(ios, ep));

    ttt::Game* game = new ttt::Game();
    int i;
    int j;

    client->onConnected([&client]() {
        client->request(
           "init", 
           std::bind(
                requestInit,
                client,
                std::placeholders::_1
            )
        );
    });

    client->connect();

    ios.run();

    while(!anyWin){
        client->request(
           "board", 
           std::bind(
                requestBoard,
                client,
                std::placeholders::_1
            )
        );

        while(!valid){
            std::cout << "Line to play " << player << " : " << std::endl;
            std::cin >> i;
            std::cout << "Column to play " << player << " : " << std::endl;
            std::cin >> j;
            
            std::string play = std::to_string(i) + "|" + std::to_string(j);

            client->request(
               "play|"+play, 
               std::bind(
                    requestPlay,
                    client,
                    std::placeholders::_1
                )
            );

            if(!valid){
                std::cout << "Invalid play!" << std::endl;
            }
        }

        valid = false;

        client->request(
           "anyWin", 
           std::bind(
                requestAnyWin,
                client,
                std::placeholders::_1
            )
        );

        client->request(
           "changeTurn", 
           std::bind(
                requestChangeTurn,
                client,
                std::placeholders::_1
            )
        );

        if(playerTurn){
            player = 'X';
        } else{
            player = 'O';
        }

    }

    client->request(
       "board", 
       std::bind(
            requestBoard,
            client,
            std::placeholders::_1
        )
    );

    client->request(
       "draw", 
       std::bind(
            requestDraw,
            client,
            std::placeholders::_1
        )
    );

    client->request(
       "winner", 
       std::bind(
            requestWinner,
            client,
            std::placeholders::_1
        )
    );

    if(draw){
        std::cout << "It's a draw!";
    } else{
        if(winner){
            std::cout << "Player 1 wins!";
        } else{
            std::cout << "Player 2 wins";
        }
    }

    return 0;
}