#include "server.h"
#include "connection.h"
#include "sockpp/tcp_socket.h"
#include "sockpp/tcp_acceptor.h"
#include <iostream>
#include "MeySQLConfig.h"

using namespace std;

MeySQL::Connect::Server::Server(){}

MeySQL::Connect::Server::~Server(){}

void MeySQL::Connect::Server::run(){
    int16_t port = MeySQL_PORT;
    cout << "Initializing on PORT: " << port << endl;
    sockpp::tcp_acceptor acc(port);

    if (!acc){
        cerr << "Error creating the acceptor: " << acc.last_error_str() << endl;
        exit(1);
    }

    while (true) {
        cout << "Waiting for connection ..." << endl;
        sockpp::tcp_socket sock = acc.accept();

        if (!sock) {
            cerr << "Error accepting incoming connection: "
                << acc.last_error_str() << endl;
        }
        else {
            // MeySQL::Connect::Connection(move(sock)).start();
            auto conn = new Connection(move(sock));
            Connection::thread_loop(conn);
        }
    }
}