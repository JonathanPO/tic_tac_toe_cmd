#ifndef CONNECTION_H
#define CONNECTION_H

#include "definitions.h"
#include "CommunicationChannel.h"
#include <functional>


namespace net 
{
    class Connection 
    {
        public:
            using OnMessageHandler = std::function<void(net::CommunicationChannel&, std::string)>;
            Connection(net::io_service& io_service);
            net::socket& socket();
            void onMessage(OnMessageHandler handler);
            void start();

        private:
            void handleRead(std::string);
            void handleWrite();
            net::socket_ptr socket_;
            std::shared_ptr<net::CommunicationChannel> channel_;
            OnMessageHandler handler_;
    };
};

#endif