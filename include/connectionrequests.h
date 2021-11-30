#ifndef MEYSQL_CONNECT_CONNECTIONREQUESTS_H
#define MEYSQL_CONNECT_CONNECTIONREQUESTS_H

#include <string>
#include <boost/property_tree/ptree.hpp>

using namespace std;

namespace MeySQL{
    namespace Connect{
        namespace ConnectionRequests{
            enum ResponseCode {
                OK,
                ERROR,
                NOCOMMAND
            };

            ResponseCode handle_request_inner(const boost::property_tree::ptree& req, boost::property_tree::ptree& res);
            void append_status(ResponseCode rescode, boost::property_tree::ptree& res);
            ResponseCode handle_request(const boost::property_tree::ptree& req, boost::property_tree::ptree& res);

            void check_active(const boost::property_tree::ptree& req, boost::property_tree::ptree& res);
            void server_config(const boost::property_tree::ptree& req, boost::property_tree::ptree& res);
        }
    }
}

#endif