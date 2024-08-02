#include <string>
#include "Command.h"
#include "Helpers.cpp"

static class CommandProcessor
{
public:
    static void initCommand()
    {
        string database = helpers::PromptDatabase();
        while (true)
        {
            string command = helpers::PromptCommand();

            if (helpers::ValidateInput(command) && helpers::ValidateInput(database))
            {
                auto account = shared_ptr<Command>(new Command(command, database));
                account->Init();
            }
        }
    }
};