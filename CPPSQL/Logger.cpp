#include <iostream>

using namespace std;

static class Logger
{
public: 
	static void LogInformation(string info) { cout << info << endl; }
    static void LogError(string error) { cerr << error << endl; }
};