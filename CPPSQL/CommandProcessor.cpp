#include <string>
#include "Command.h"
#include "Helpers.cpp"
#include "Logger.cpp"

static class CommandProcessor
{
private:
    static const int commandReadLimit = 10000;

public:
    static void initCommand()
    {
        string database = helpers::PromptDatabase();
        if (helpers::ValidateInput(database))
        {
            auto account = shared_ptr<Command>(new Command(commandReadLimit));
            account->SetupConnection(database);
            promptAndInitCommand(account);
        }
        else
        {
            Logger::LogInformation("Could not connect to the database -> " + database)
        }
    }

private:
    void promptAndInitCommand(Command& account)
    {
        while (true)
        {
            string command = helpers::PromptCommand();

            if (helpers::ValidateInput(command))
            {
                account->Init(command);
            }
        }
    }
};