//
// Created by root on 18-9-5.
//

#include "Logparser.h"

void Logparser::parser_log() {
    sqlite3* db;
    const char *key = "000000";
    int re = sqlite3_open("roycom.db", &db);
    if(re == SQLITE_OK){
        int n = sqlite3_key(db, key, (int)strlen(key));
    }

    string messages_path = this->logname_map["messages"];

    JsonObject& root = jsonBuffer.createObject();

    JsonObject& nextRoot = root.createNestedObject("log");
}
