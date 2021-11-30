#include "connectionrequests.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include "MeySQLConfig.h"

using namespace std;

MeySQL::Connect::ConnectionRequests::ResponseCode MeySQL::Connect::ConnectionRequests::handle_request_inner(const boost::property_tree::ptree& req, boost::property_tree::ptree& res){
    try{
        bool found = false;
        auto command = req.get<string>("command");

        boost::property_tree::ptree data;
        res.add_child("data", data);

        if(command == "check-active"){
            found = true;
            check_active(req,data);
        }
        else if(command == "server-config"){
            found = true;
            server_config(req,data);
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

void MeySQL::Connect::ConnectionRequests::append_status(MeySQL::Connect::ConnectionRequests::ResponseCode rescode, boost::property_tree::ptree& res){
    switch (rescode) {
        case OK:
            res.put("status", "OK");
            break;
        case ERROR:
            res.put("status", "ERROR");
            break;
        case NOCOMMAND:
            res.put("status", "NOCOMMAND");
            break;
    }
}

MeySQL::Connect::ConnectionRequests::ResponseCode MeySQL::Connect::ConnectionRequests::handle_request(const boost::property_tree::ptree& req, boost::property_tree::ptree& res){
    auto rescode = handle_request_inner(req, res);
    MeySQL::Connect::ConnectionRequests::append_status(rescode, res);
    return rescode;
}

void MeySQL::Connect::ConnectionRequests::check_active(const boost::property_tree::ptree& req, boost::property_tree::ptree& res){}

void MeySQL::Connect::ConnectionRequests::server_config(const boost::property_tree::ptree& req, boost::property_tree::ptree& res){
    res.put("version-major", MeySQL_VERSION_MAJOR);
    res.put("version-minor", MeySQL_VERSION_MINOR);
    res.put("MeySQL_PORT", MeySQL_PORT);
}