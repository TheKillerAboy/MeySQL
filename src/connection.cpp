#include "connection.h"
#include <thread>
#include "sockpp/tcp_socket.h"
#include <string>
#include "boost/log/trivial.hpp"
#include <iostream>
#include "connectionrequests.h"
#include <boost/json.hpp>

using namespace boost;
using namespace std;

MeySQL::Connect::Connection::Connection(){
    sock = nullptr;
    thr = nullptr;
    id = current_id++;
}

MeySQL::Connect::Connection::Connection(sockpp::tcp_socket sock_){
    sock = new sockpp::tcp_socket;
    thr = nullptr;
    *sock = std::move(sock_);
    id = current_id++;
}

size_t MeySQL::Connect::Connection::current_id = 0;

MeySQL::Connect::Connection::~Connection(){}

void MeySQL::Connect::Connection::thread_loop(Connection* con){
    BOOST_LOG_TRIVIAL(debug) << "Created thread for " << *con;

    try{
        auto req = con->recieve();

        json::object req_json = json::parse(req).as_object();

        json::object res_json;
        MeySQL::Connect::ConnectionRequests::handle_request(req_json, res_json);

        auto res = json::serialize(res_json);
        con->send(res);
    }
    catch (const std::exception& e){
        if(con->get_socket()){
            BOOST_LOG_TRIVIAL(error) << e.what();

            try{
                json::object res_json;
                MeySQL::Connect::ConnectionRequests::append_status(MeySQL::Connect::ConnectionRequests::ResponseCode::ERROR, res_json);
                auto res = json::serialize(res_json);
                con->send(res);
            }
            catch(...){}
        }
    }

    BOOST_LOG_TRIVIAL(debug) << "Deleting thread for " << *con;
    delete con;
}

void MeySQL::Connect::Connection::start(){
    BOOST_LOG_TRIVIAL(debug) << "Creating thread for " << *this;

    thr = new thread(MeySQL::Connect::Connection::thread_loop, this);
    thr->detach();
}

sockpp::tcp_socket* MeySQL::Connect::Connection::get_socket(){
    return sock;
}

size_t MeySQL::Connect::Connection::get_id() const{
    return id;
}

void MeySQL::Connect::Connection::send(const string& msg){
    BOOST_LOG_TRIVIAL(info) << "Sending: \"" << msg << "\" on " << *this;
    get_socket()->write(msg);
}

string MeySQL::Connect::Connection::recieve(){
    char buf[PAYLOAD_BUFFER_SIZE];
    size_t size =  get_socket()->read(buf, PAYLOAD_BUFFER_SIZE);
    string msg(buf, size);
    BOOST_LOG_TRIVIAL(info) << "Recieved: \"" << msg << "\" on " << *this;
    return msg;
}

ostream& MeySQL::Connect::operator<<(ostream& os, const MeySQL::Connect::Connection& con){
    os << "Connection<ID:" << con.get_id() << ">";

    return os;
}