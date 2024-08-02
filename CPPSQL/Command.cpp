#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "Command.h"
#include <fstream>
#include <json/json.h>
#include "UserConfig.h"
#include "Logger.cpp"
#include <direct.h>  

using namespace std;

Command::Command(string command, string database) : command(command), database(database) { }

void Command::Init()
{
    int rowLimit = 10000;
    try
    {
        auto statement = SetupConnection();
        auto result = statement->executeQuery(command);

        Logger::LogInformation("---------------------------- executing query");
        while (result->next())
        {
            Logger::LogInformation("------------- row start");
            for (int index = 1; index < rowLimit; index++)
            {
                try
                {
                    auto fullResult = result->getString(index);
                    cout << fullResult << endl;
                    Logger::LogInformation("------");
                }
                catch(...)
                {
                    break;
                }
            }
            Logger::LogInformation("------------- row end");
        }

        Logger::LogInformation("---------------------------- success -- query executed");
    }
    catch (sql::SQLException& ex)
    {
        Fallback(ex);
    }
}

sql::Statement* Command::SetupConnection()
{
    sql::Driver* driver = get_driver_instance();

    UserConfig* config = GetConfig();

    sql::Connection* connection = driver->connect(config->GetUrl().asCString(), config->GetUsername().asCString(), config->GetPassword().asCString());

    connection->setSchema(database);
    auto statement = connection->createStatement();

    return statement;
}

void Command::Fallback(sql::SQLException ex)
{
    auto errorCode = ex.getErrorCode();
    if (errorCode != 0)
    {
        Logger::LogInformation("error occured");

        cout << errorCode << endl;
        cout << ex.getSQLState() << endl;
    }
    else
    {
        Logger::LogInformation("success -- command executed");
    }
}

UserConfig* Command::GetConfig()
{
    Json::Value read_file;

    auto directory = GetCurrentDirectory();

    ifstream file(directory + "/appsettings.json");

    if (!file.is_open())
    {
        cout << "failed to open appsettings.json file" << endl;
    }

    file >> read_file;

    auto config = new UserConfig(read_file["url"], read_file["username"], read_file["password"]);

    return config;
}

string Command::GetCurrentDirectory()
{
    const size_t size = 1024;
    char buffer[size];

    if (_getcwd(buffer, size) == NULL) {
        cerr << "Error reading directory for search of appsettings.json" << endl;
    }
    return buffer;
}

