#pragma once
#include <string>
#include "mysql_connection.h"
#include "UserConfig.h"
#include "ConnectionDetails.h"

using namespace std;

class Command
{
private:
    sql::Statement* connection;
    int columnReadLimit;

public:
    Command(int columnReadLimit);
    ~Command();
    void Init(string command);
    bool SetupConnection(ConnectionDetails* connectionDetails);

private:
    UserConfig* GetConfig();
    string GetCurrentDirectory();
    void Fallback(sql::SQLException);
};