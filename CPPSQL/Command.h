#pragma once
#include <string>
#include "mysql_connection.h"
#include "UserConfig.h"

using namespace std;

class Command
{
private:
    string command, database;

public:
    Command(string command, string database);
    void Init();
    
private:
    sql::Statement* SetupConnection();
    UserConfig* GetConfig();
    string GetCurrentDirectory();
    void Fallback(sql::SQLException);
};