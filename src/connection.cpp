#include "connection.h"
#include <thread>
#include "sockpp/tcp_socket.h"

MeySQL::Connect::Connection::Connection(sockpp::tcp_socket sock_){
    sock = std::move(sock_);
}

MeySQL::Connect::Connection::~Connection(){}

void MeySQL::Connect::Connection::thread_loop(Connection* con){

}

void MeySQL::Connect::Connection::start(){
    thr = std::thread(MeySQL::Connect::Connection::thread_loop, this);
    thr.detach();
}