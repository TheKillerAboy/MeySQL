#ifndef MEYSQL_CONNECT_CONNECTIONREQUESTS_H
#define MEYSQL_CONNECT_CONNECTIONREQUESTS_H

#include <string>

#include <boost/json.hpp>

using namespace std;

namespace MeySQL{
    namespace Connect{
        namespace ConnectionRequests{
            enum ResponseCode {
                OK,
                ERROR,
                NOCOMMAND
            };

            ResponseCode handle_request_inner(const boost::json::object& req, boost::json::object& res);
            void append_status(ResponseCode rescode, boost::json::object& res);
            ResponseCode handle_request(const boost::json::object& req, boost::json::object& res);

            void check_active(const boost::json::object& req, boost::json::object& res);
            void server_config(const boost::json::object& req, boost::json::object& res);
        }
    }
}

#endif