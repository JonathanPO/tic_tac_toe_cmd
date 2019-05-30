#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <memory>
#include <boost/asio.hpp>

namespace net {
    using ip_address    = boost::asio::ip::address;
    using ip_address_v4 = boost::asio::ip::address_v4;
    using error_code    = boost::system::error_code;
    using endpoint      = boost::asio::ip::tcp::endpoint;
    using io_service    = boost::asio::io_service;
    using socket        = boost::asio::ip::tcp::socket;
    using socket_ptr    = std::shared_ptr<boost::asio::ip::tcp::socket>;
    using acceptor      = boost::asio::ip::tcp::acceptor;
    using streambuf     = boost::asio::streambuf;
    using streambuf_ptr = std::shared_ptr<boost::asio::streambuf>;
};

#endif