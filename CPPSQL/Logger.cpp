#pragma once
#include <iostream>

using namespace std;

static class Logger
{
public: 
	static void LogInformation(string info) { cout << "\n" + info << endl; }
    static void LogError(string error) { cerr << "ERROR: " + error << endl; }
};