#ifndef MEYSQL_CONNECT_CONNECTIONREQUESTS_H
#define MEYSQL_CONNECT_CONNECTIONREQUESTS_H

#include <string>

#include <boost/json.hpp>

using namespace boost;
using namespace std;

namespace MeySQL{
    namespace Connect{
        namespace ConnectionRequests{
            enum ResponseCode {
                OK,
                ERROR,
                NOCOMMAND
            };

            ResponseCode handle_request_inner(const json::object& req, json::object& res);
            void append_status(ResponseCode rescode, json::object& res);
            ResponseCode handle_request(const json::object& req, json::object& res);

            void check_active(const json::object& req, json::object& res);
            void server_config(const json::object& req, json::object& res);
        }
    }
}

#endif