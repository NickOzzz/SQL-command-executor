#include <string>
#include "Command.h"
#include "Helpers.cpp"
#include "Logger.cpp"
#include "ConnectionDetails.h"

using namespace std;

static class CommandProcessor
{
private:
    static const int CommandReadLimit = 10000;

public:
    static void InitCommand()
    {
        string useConfig = Helpers::PromptConfigurationUsage();
        useConfig = Helpers::RemoveWhiteSpaces(useConfig);

        string url = "";
        string username = "";
        string password = "";

        if (useConfig != "y" && useConfig != "Y")
        {
            url = Helpers::PromptUrl();
            username = Helpers::PromptUsername();
            password = Helpers::PromptPassword();
        }

        string database = Helpers::PromptDatabase();

        auto connectionDetails = shared_ptr<ConnectionDetails>(new ConnectionDetails(useConfig, url, username, password, database));

        if (!Helpers::ValidateConnectionDetails(connectionDetails.get()))
        {
            Logger::LogError("Connection details have to be provided when default configuration is not used");
            return;
        }

        if (!Helpers::ValidateInput(database)) 
        {
            Logger::LogError("Database name has to be provided");
            return;
        }

        auto account = shared_ptr<Command>(new Command(CommandReadLimit));

        auto success = account->SetupConnection(connectionDetails.get());
        
        if (success) 
        {
            PromptAndInitCommand(account.get());
        }
    }

private:
    static void PromptAndInitCommand(Command* account)
    {
        while (true)
        {
            string command = Helpers::PromptCommand();

            if (command == "/quit") 
            {
                return;
            }

            if (Helpers::ValidateInput(command))
            {
                account->Init(command);
            }
            else 
            {
                Logger::LogError("Command cannot be empty");
            }
        }
    }
};