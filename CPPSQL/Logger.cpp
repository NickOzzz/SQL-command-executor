#include <iostream>

using namespace std;

static class Logger
{
public: 
	static void LogInformation(string info) { cout << info << endl; }
};