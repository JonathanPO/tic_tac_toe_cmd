#include <memory>
#include <functional>
#include <iostream>
#include "Server.h"

net::Server::Server(net::io_service& io_service, net::endpoint ep){
	: io_service_(io_service), 
	acceptor_(io_service, ep)
}

void net::Server::start(){
	startAccepting();
}

void net::Server::OnConnect(net::Server::OnConnectHandler handler){
	onConnectHandler_ = handler;
}

void net::Server::onMessage(OnMessageHandler handler){
	handler_ = handler;
}

void net::Server::handleAccept(const net::error_code& ec, std::shared_ptr<net::Connection> conn){
	if(!ec){
		connections_.push_back(conn);
		if(onMessageHandler_){
			conn->onMessage(onMessageHandler_);
		}
		conn->start();
		if(onConnectHandler_){
			onConnectHandler_(*conn);
		}
	}
}
			
void net::Server::startAccepting(){
	std::shared_ptr<net::Connection> conn(new net::Connection(io_service_));

	acceptor_.async_accept(
		conn->socket(), 
		std::bind(
			&net::Server::handleAccept, 
			this, 
			std::placeholders::_1, 
			conn
		)
	);
}