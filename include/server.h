#ifndef MEYSQL_CONNECT_SERVER_H
#define MEYSQL_CONNECT_SERVER_H

#include <list>
#include <pthread.h>
#include "connection.h"

namespace MeySQL{
    namespace Connect{
        class Server{
        private:
        public:
            Server();
            ~Server();

            void run();
        };
    }
}

#endif