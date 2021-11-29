#include "server.h"
#include "connection.h"
#include "sockpp/tcp_socket.h"
#include "sockpp/tcp_acceptor.h"
#include <iostream>
#include "MeySQLConfig.h"
#include "boost/log/trivial.hpp"

using namespace std;

MeySQL::Connect::Server::Server(){}

MeySQL::Connect::Server::~Server(){}

void MeySQL::Connect::Server::run(){
    int16_t port = MeySQL_PORT;

    BOOST_LOG_TRIVIAL(info) << "Initializing on PORT: " << port;
    sockpp::tcp_acceptor acc(port);

    if (!acc){
        BOOST_LOG_TRIVIAL(error) << "Error creating the acceptor: " << acc.last_error_str();
        exit(1);
    }

    while (true) {
        BOOST_LOG_TRIVIAL(info) << "Waiting for connection ...";
        sockpp::tcp_socket sock = acc.accept();

        if (!sock) {
            BOOST_LOG_TRIVIAL(error) << "Error accepting incoming connection: " << acc.last_error_str();
        }
        else {
            // MeySQL::Connect::Connection(move(sock)).start();
            auto conn = new Connection(move(sock));
            Connection::thread_loop(conn);
        }
    }
}