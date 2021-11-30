#include "server.h"
#include "connection.h"

#include <iostream>

using namespace std;

int main(){
    MeySQL::Connect::Server server;
    server.run();
}