#ifndef MEYSQL_CONNECT_CONNECTION_H
#define MEYSQL_CONNECT_CONNECTION_H

#include "sockpp/tcp_socket.h"
#include <thread>
#include <string>

namespace MeySQL{
    namespace Connect{
        class Connection{
        private:
            sockpp::tcp_socket sock;
            std::thread thr;

            static const size_t PAYLOAD_BUFFER_SIZE = 1024;
        public:
            Connection(sockpp::tcp_socket sock_);
            ~Connection();

            void start();

            static void thread_loop(Connection* con);

            sockpp::tcp_socket& get_socket();

            void send(const std::string& msg);
            std::string recieve();
        };
    }
}

#endif