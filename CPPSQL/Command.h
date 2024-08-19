#pragma once
#include <string>
#include "mysql_connection.h"
#include "UserConfig.h"

using namespace std;

class Command
{
private:
    Statement* connection;
    int columnReadLimit;

public:
    Command(int columnReadLimit);
    ˜Command();
    void Init(string command);
    
private:
    void SetupConnection(string database);
    UserConfig* GetConfig();
    string GetCurrentDirectory();
    void Fallback(sql::SQLException);
};