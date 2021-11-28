#include "connection.h"
#include <thread>
#include "sockpp/tcp_socket.h"
#include <string>
#include <iostream>

using namespace std;

MeySQL::Connect::Connection::Connection(sockpp::tcp_socket sock_){
    sock = move(sock_);
}

MeySQL::Connect::Connection::~Connection(){}



void MeySQL::Connect::Connection::thread_loop(Connection* con){
    string msg = con->recieve();
    con->send("Hello World");
}

void MeySQL::Connect::Connection::start(){
    thr = thread(MeySQL::Connect::Connection::thread_loop, this);
    thr.detach();
}

sockpp::tcp_socket& MeySQL::Connect::Connection::get_socket(){
    return sock;
}

void MeySQL::Connect::Connection::send(const string& msg){
    cout << "Sending: " << msg << " ";
    cout << get_socket().write(msg) << endl;
}

string MeySQL::Connect::Connection::recieve(){
    char buf[PAYLOAD_BUFFER_SIZE];
    size_t size =  get_socket().read(buf, PAYLOAD_BUFFER_SIZE);
    string msg(buf, size);
    cout << "Recieved: " << msg << endl;
    return msg;
}