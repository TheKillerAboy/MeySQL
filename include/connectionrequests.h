#ifndef MEYSQL_CONNECT_CONNECTIONREQUESTS_H
#define MEYSQL_CONNECT_CONNECTIONREQUESTS_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

namespace MeySQL{
    namespace Connect{
        namespace ConnectionRequests{
            enum ResponseCode {
                OK,
                EXIT,
                ERROR,
                NOCOMMAND
            };

            ResponseCode handle_request_inner(const boost::property_tree::ptree& req, boost::property_tree::ptree& res);
            ResponseCode handle_request(const boost::property_tree::ptree& req, boost::property_tree::ptree& res);
        }
    }
}

#endif