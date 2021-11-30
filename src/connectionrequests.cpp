#include "connectionrequests.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>

using namespace std;

MeySQL::Connect::ConnectionRequests::ResponseCode MeySQL::Connect::ConnectionRequests::handle_request_inner(const boost::property_tree::ptree& req, boost::property_tree::ptree& res){
    try{
        bool found = false;
        if(req.get<string>("command") == "exit"){
            return EXIT;
        }
        if(found){
            return OK;
        }
        else{
            return NOCOMMAND;
        }
    }
    catch(const exception& e){
        res.put("status-reason", e.what());
        return ERROR;
    }
}

MeySQL::Connect::ConnectionRequests::ResponseCode MeySQL::Connect::ConnectionRequests::handle_request(const boost::property_tree::ptree& req, boost::property_tree::ptree& res){
    auto rescode = handle_request_inner(req, res);
    switch (rescode) {
        case OK:
            res.put("status", "OK");
            break;
        case EXIT:
            res.put("status", "EXIT");
            break;
        case ERROR:
            res.put("status", "ERROR");
            break;
        case NOCOMMAND:
            res.put("status", "NOCOMMAND");
            break;
    }
    return rescode;
}