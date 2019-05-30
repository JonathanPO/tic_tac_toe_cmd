#include "Connection.h"
#include <functional>

net::Connection::Connection(net::io_service& io_service)
    : socket_(new net::socket(io_service)),
      channel_(new net::CommunicationChannel(socket_))
{
    channel_->onRead(
        std::bind(
            &net::Connection::handleRead,
            this,
            std::placeholders::_1
        )
    );
    channel_->onWrite(
         std::bind(
            &net::Connection::handleWrite,
            this
        )
    );
}

void net::Connection::start() 
{
    channel_->read();
}

void net::Connection::onMessage(OnMessageHandler handler)
{
    handler_ = handler;
}


void net::Connection::handleRead(std::string request) 
{
    if (handler_) {
        handler_(*channel_, request);
    }
}

void net::Connection::handleWrite()
{
    channel_->read();
}

net::socket& net::Connection::socket() 
{
    return *socket_;
}