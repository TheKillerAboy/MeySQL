#include "connection.h"
#include <thread>
#include "sockpp/tcp_socket.h"
#include <string>
#include <iostream>

MeySQL::Connect::Connection::Connection(sockpp::tcp_socket sock_){
    sock = std::move(sock_);
}

MeySQL::Connect::Connection::~Connection(){}



void MeySQL::Connect::Connection::thread_loop(Connection* con){
    std::string msg = con->recieve();
    con->send("Hello World");
}

void MeySQL::Connect::Connection::start(){
    thr = std::thread(MeySQL::Connect::Connection::thread_loop, this);
    thr.detach();
}

sockpp::tcp_socket& MeySQL::Connect::Connection::get_socket(){
    return sock;
}

void MeySQL::Connect::Connection::send(const std::string& msg){
    std::cout << "Sending: " << msg << " ";
    std::cout << get_socket().write(msg) << std::endl;
}

std::string MeySQL::Connect::Connection::recieve(){
    char buf[PAYLOAD_BUFFER_SIZE];
    size_t size =  get_socket().read(buf, PAYLOAD_BUFFER_SIZE);
    std::string msg(buf, size);
    std::cout << "Recieved: " << msg << std::endl;
    return msg;
}