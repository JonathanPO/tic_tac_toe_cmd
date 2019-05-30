#ifndef CLIENT_H
#define CLIENT_H

#include "definitions.h"
#include "CommunicationChannel.h"
#include <functional>
#include <memory>

namespace net {
    class Client 
    {
        public:
            using OnConnectedHandler = std::function<void()>;
            using ResponseHandler    = std::function<void(std::string)>;

            Client(net::io_service& io_service, net::endpoint ep);
            void connect();
            bool isConnected();
            net::socket& socket();
            net::socket_ptr socketPtr();
            void onConnected(net::Client::OnConnectedHandler handler);
            void request(std::string, ResponseHandler handler);

        private:
            net::socket_ptr socket_;
            net::endpoint endpoint_;
            bool connected_;
            net::Client::OnConnectedHandler onConnectedHandler_;

            void handleConnect(net::error_code ec);
            std::shared_ptr<net::CommunicationChannel> channel_;

    };

};

#endif