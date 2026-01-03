#pragma once
#include <string>

using namespace std;

class ConnectionDetails
{
private:
	string UseConfig, Url, Username, Password, Database;

public:
	ConnectionDetails(string useConfig, string url, string username, string password, string database);
	string GetUseConfig();
	string GetUrl();
	string GetUsername();
	string GetPassword();
	string GetDatabase();
};