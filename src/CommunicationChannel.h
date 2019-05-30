#ifndef COMMUNICATION_CHANNEL_H
#define COMMUNICATION_CHANNEL_H

#include "definitions.h"
#include <functional>
#include <string>

namespace net {
    class CommunicationChannel 
    {
        public:
            static const std::string MESSAGE_SEPARATOR;

            using OnReadHandler  = std::function<void(std::string)>;
            using OnWriteHandler = std::function<void()>;

            CommunicationChannel(net::socket_ptr socket);

            virtual ~CommunicationChannel();
            virtual void onRead(OnReadHandler handler);
            virtual void onWrite(OnWriteHandler handler);
            virtual void read();
            virtual void write(std::string message);
            virtual void handleRead(net::error_code ec, net::streambuf_ptr buffer);
            virtual void handleWrite(net::error_code ec, net::streambuf_ptr buffer);

        private:
            net::socket_ptr socket_;
            OnReadHandler onReadHandler_;
            OnWriteHandler onWriteHandler_;
    };
};

#endif