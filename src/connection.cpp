#include "connection.h"
#include <thread>
#include "sockpp/tcp_socket.h"
#include <string>
#include "boost/log/trivial.hpp"
#include <iostream>
#include "connectionrequests.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

using namespace std;

MeySQL::Connect::Connection::Connection(){
    sock = nullptr;
    thr = nullptr;
    id = current_id++;
}

MeySQL::Connect::Connection::Connection(sockpp::tcp_socket sock_){
    sock = new sockpp::tcp_socket;
    thr = nullptr;
    *sock = move(sock_);
    id = current_id++;
}

size_t MeySQL::Connect::Connection::current_id = 0;

MeySQL::Connect::Connection::~Connection(){}

void MeySQL::Connect::Connection::thread_loop(Connection* con){
    BOOST_LOG_TRIVIAL(debug) << "Created thread for " << *con;

    try{
        auto req = con->recieve();

        boost::property_tree::ptree req_json;
        istringstream is(req);
        boost::property_tree::read_json(is, req_json);

        boost::property_tree::ptree res_json;
        auto rescode = MeySQL::Connect::ConnectionRequests::handle_request(req_json, res_json);

        std::ostringstream res_buf; 
        boost::property_tree::write_json (res_buf, res_json, false);

        auto res = res_buf.str();
        con->send(res);
    }
    catch (const exception& e){
        if(con->get_socket()){
            BOOST_LOG_TRIVIAL(error) << e.what();

            try{
                boost::property_tree::ptree res_json;
                MeySQL::Connect::ConnectionRequests::append_status(MeySQL::Connect::ConnectionRequests::ResponseCode::ERROR, res_json);
                std::ostringstream res_buf; 
                boost::property_tree::write_json (res_buf, res_json, false);
                auto res = res_buf.str();
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