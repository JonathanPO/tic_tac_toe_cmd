#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <memory>
#include <functional>
#include "definitions.h"
#include "Connection.h"

namespace net
{
    class Server 
    {
        public:
            using OnConnectHandler = std::function<void(net::Connection&)>; 
            using OnMessageHandler = std::function<void(net::CommunicationChannel&, std::string)>;

            Server(net::io_service& io_service, net::endpoint ep);
            void start();
            void onConnect(OnConnectHandler handler);
            void onMessage(OnMessageHandler handler);

        private:
            net::io_service& io_service_;
            net::acceptor acceptor_;
            std::vector<std::shared_ptr<net::Connection>> connections_;
            OnConnectHandler onConnectHandler_;
            OnMessageHandler onMessageHandler_;

            void handleAccept(
                const net::error_code& ec, 
                std::shared_ptr<net::Connection> conn
            );
            void startAccepting();

    };
    
};

#endif