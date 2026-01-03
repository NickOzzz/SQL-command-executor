#pragma once
#include <string>
#include <iostream>
#include "Logger.cpp"
#include "ConnectionDetails.h"

using namespace std;

static class Helpers
{
public:
    static void DisplayWelcomeMessage() 
    {
        Logger::LogInformation("WELCOME TO MYSQL COMMAND EXECUTOR! \n =================================");
    }

    static string PromptConfigurationUsage()
    {
        string useConfig;

        Logger::LogInformation("would you like to use configuration from appsettings.json? (y/n): ");
        cin >> useConfig;
        cin.ignore();

        return useConfig;
    }

    static string PromptUrl()
    {
        string url;

        Logger::LogInformation("provide url to your server: ");
        cin >> url;
        cin.ignore();

        return url;
    }

    static string PromptUsername()
    {
        string username;

        Logger::LogInformation("provide your username for server access: ");
        cin >> username;
        cin.ignore();

        return username;
    }

    static string PromptPassword()
    {
        string password;

        Logger::LogInformation("provide your password for server access: ");
        cin >> password;
        cin.ignore();

        return password;
    }
    
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

        Logger::LogInformation("provide your command(type '/quit' to finnish): ");
        getline(cin, command);

        return command;
    }

    static bool ValidateInput(string command)
    {
        return command != "";
    }

    static bool ValidateConnectionDetails(ConnectionDetails* connectionDetails) 
    {
        auto useConfig = connectionDetails->GetUseConfig();
        auto url = connectionDetails->GetUrl();
        auto username = connectionDetails->GetUsername();
        auto password = connectionDetails->GetPassword();

        return !(
            (useConfig != "y" && useConfig != "Y") 
            && (!Helpers::ValidateInput(url) || !Helpers::ValidateInput(username) || !Helpers::ValidateInput(password))
            );
    }

    static string RemoveWhiteSpaces(string item) 
    {
        item.erase(remove(item.begin(), item.end(), ' '), item.end());
        return item;
    }
};