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

Command::Command(int columnReadLimit) : columnReadLimit(columnReadLimit) {}

Command::˜Command()
{
    delete this->connection;
}

void Command::Init(string command)
{
    try
    {
        auto result = this->connection->executeQuery(command);

        Logger::LogInformation("---------------------------- executing query");
        while (result->next())
        {
            Logger::LogInformation("------------- row start");
            for (int index = 1; index <= columnReadLimit; index++)
            {
                try
                {
                    auto fullResult = result->getString(index);
                    Logger::LogInformation(fullResult);
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

void Command::SetupConnection(string database)
{
    sql::Driver* driver = get_driver_instance();

    UserConfig* config = GetConfig();

    sql::Connection* connection = driver->connect(config->GetUrl().asCString(), config->GetUsername().asCString(), config->GetPassword().asCString());

    delete config;

    connection->setSchema(database);
    auto statement = connection->createStatement();

    this->connection = statement;
}

void Command::Fallback(sql::SQLException ex)
{
    auto errorCode = ex.getErrorCode();
    if (errorCode != 0)
    {
        Logger::LogError("error occured");

        Logger::LogError(errorCode);
        Logger::LogError(ex.getSQLState());
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
        Logger::LogError("failed to open appsettings.json file");
    }

    file >> read_file;

    auto config = new UserConfig(read_file["url"], read_file["username"], read_file["password"]);

    delete file;
    delete read_file;

    return config;
}

string Command::GetCurrentDirectory()
{
    const size_t size = 1024;
    char buffer[size];

    if (_getcwd(buffer, size) == NULL) {
        Logger::LogError("Error reading directory for search of appsettings.json");
    }
    return buffer;
}

