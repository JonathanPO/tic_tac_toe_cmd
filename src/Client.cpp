#include "Client.h"

net::Client::Client(net::io_service& io_service, net::endpoint ep){
	: socket_(new net::socket(io_service)), 
	endpoint_(ep), 
	channel_(new net::CommunicationChannel(socket_))
}

void net::Client::connect(){
	boost::asio::async_connect(
		endpoint_, 
		std::bind(
			&net::Client::handleConnect, 
			this, 
			std::placeholders::_1
		)
	);
}

bool net::Client::isConnected(){
	return connected_;
}

net::socket& net::Client::socket(){
	return *socket_;
}

void net::Client::onConnected(net::Client::OnConnectedHandler handler){
	OnConnectedHandler_ = handler;
}

void net::Client::request(std::string, ResponseHandler handler){
	auto self = this;
	channel_->onWrite([self](){
		self->channel_->read();
	});

	channel_->onRead([handler](std::string response)){
		handler(response);
	}

	channel_->write(request);
}

void net::Client::handleConnect(net::error_code ec){
	if(ec){
		return;
	}
	connected_ = true;
	if(onConnectedHandler_){
		onConnectedHandler_();
	}
}

