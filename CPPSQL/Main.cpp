#include <iostream>
#include "CommandProcessor.cpp"
#include "Helpers.cpp"


using namespace std;

int main()
{
    Helpers::DisplayWelcomeMessage();
    CommandProcessor::InitCommand();
    return 0;
}