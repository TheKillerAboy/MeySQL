#include "connectionrequests.h"

#include <string>
#include "MeySQLConfig.h"
#include <boost/json.hpp>

using namespace boost;
using namespace std;

MeySQL::Connect::ConnectionRequests::ResponseCode
MeySQL::Connect::ConnectionRequests::handle_request_inner(
    const json::object& req, json::object& res) {
    try {
        bool found = false;
        auto command = req.at("command").as_string();

        json::object data;
        res["data"] = data;

        if(command == "check-active") {
            found = true;
            check_active(req,data);
        } else if(command == "server-config") {
            found = true;
            server_config(req,data);
        }
        if(found) {
            return OK;
        } else {
            return NOCOMMAND;
        }
    } catch(const std::exception& e) {
        res["status-reason"] = e.what();
        return ERROR;
    }
}

void MeySQL::Connect::ConnectionRequests::append_status(
    MeySQL::Connect::ConnectionRequests::ResponseCode rescode, json::object& res) {
    switch (rescode) {
        case OK:
            res["status"] = "OK";
            break;
        case ERROR:
            res["status"] = "ERROR";
            break;
        case NOCOMMAND:
            res["status"] = "NOCOMMAND";
            break;
    }
}

MeySQL::Connect::ConnectionRequests::ResponseCode
MeySQL::Connect::ConnectionRequests::handle_request(const json::object& req,
        json::object& res) {
    auto rescode = handle_request_inner(req, res);
    MeySQL::Connect::ConnectionRequests::append_status(rescode, res);
    return rescode;
}

void MeySQL::Connect::ConnectionRequests::check_active(const json::object& req,
        json::object& res) {}

void MeySQL::Connect::ConnectionRequests::server_config(const json::object& req,
        json::object& res) {
    res["version-major"] = MeySQL_VERSION_MAJOR;
    res["version-minor"] = MeySQL_VERSION_MINOR;
    res["MeySQL_PORT"] = MeySQL_PORT;
}