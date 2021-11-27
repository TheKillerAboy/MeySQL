#include "server.h"
#include "connection.h"
#include "sockpp/tcp_socket.h"
#include "sockpp/tcp_acceptor.h"
#include <iostream>
#include "MeySQLConfig.h"

MeySQL::Connect::Server::Server(){}

MeySQL::Connect::Server::~Server(){}

void MeySQL::Connect::Server::run(){
    int16_t port = MeySQL_PORT;
    sockpp::tcp_acceptor acc(port);

    if (!acc)
        std::cerr << "Error creating the acceptor: " << acc.last_error_str() << std::endl;
        exit(1);

    while (true) {
        sockpp::tcp_socket sock = acc.accept();

        if (!sock) {
            std::cerr << "Error accepting incoming connection: "
                << acc.last_error_str() << std::endl;
        }
        else {
            MeySQL::Connect::Connection(std::move(sock)).start();
        }
    }
}