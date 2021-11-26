#ifndef MEYSQL_CONNECT_CONNECTION_H
#define MEYSQL_CONNECT_CONNECTION_H

#include "sockpp/tcp_socket.h"
#include <thread>

namespace MeySQL{
    namespace Connect{
        class Connection{
        private:
            sockpp::tcp_socket sock;
            std::thread thr;
        public:
            Connection(sockpp::tcp_socket sock_);
            ~Connection();

            void start();

            static void thread_loop(Connection* con);
        };
    }
}

#endif