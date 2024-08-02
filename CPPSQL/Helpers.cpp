#include <string>
#include <iostream>
#include "Logger.cpp"

using namespace std;

static class helpers
{
public:
    static string PromptDatabase()
    {
        string database;

        Logger::LogInformation("provide your database name: ");
        cin >> database;
        cin.ignore();

        return database;
    }

    static string PromptCommand()
    {
        string command;

        Logger::LogInformation("provide your command: ");
        getline(cin, command);

        return command;
    }

    static bool ValidateInput(string command)
    {
        return command != "";
    }
};