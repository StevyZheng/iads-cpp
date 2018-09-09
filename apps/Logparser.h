//
// Created by root on 18-9-5.
//

#ifndef IADS_LOGPARSER_H
#define IADS_LOGPARSER_H

#include "../lib/stevy.h"
#include "../lib/ArduinoJson/ArduinoJson.hpp"
extern "C" {
#define SQLITE_HAS_CODEC
#include "../lib/database/sqlcipher/sqlite3.h"
};

class Logparser {
public:
    Logparser(){
        logname_map["messages"] = "/var/log/messags";
        logname_map["mcelog"] = "/var/log/mcelog";
        logname_map["bmclog"] = "";
    }

private:
    void parser_log();

    DynamicJsonBuffer  jsonBuffer;
    string json_str;
    map<string, string> logname_map;
};


#endif //IADS_LOGPARSER_H
