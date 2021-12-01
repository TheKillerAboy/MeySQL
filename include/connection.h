#ifndef MEYSQL_CONNECT_CONNECTION_H
#define MEYSQL_CONNECT_CONNECTION_H

#include "sockpp/tcp_socket.h"
#include <thread>
#include <string>
#include <iostream>

using namespace std;

namespace MeySQL {
    namespace Connect {
        class Connection {
        private:
            static size_t current_id;

            sockpp::tcp_socket* sock;
            thread* thr;
            size_t id;

            static const size_t PAYLOAD_BUFFER_SIZE = 32767;
        public:
            Connection();
            Connection(sockpp::tcp_socket sock_);
            ~Connection();

            void start();

            static void thread_loop(Connection* con);

            sockpp::tcp_socket* get_socket();
            size_t get_id() const;

            void send(const string& msg);
            string recieve();

            friend ostream& operator<< (ostream& os, const Connection& con);
        };
    }
}

#endif