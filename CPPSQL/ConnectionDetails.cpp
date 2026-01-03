#pragma once
#include <string>
#include "ConnectionDetails.h"

using namespace std;

ConnectionDetails::ConnectionDetails(string useConfig, string url, string username, string password, string database) : UseConfig(useConfig), Url(url), Username(username), Password(password), Database(database) {}

string ConnectionDetails::GetUseConfig() 
{
	return this->UseConfig;
}

string ConnectionDetails::GetUrl() 
{
	return this->Url;
}

string ConnectionDetails::GetUsername()
{
	return this->Username;
}

string ConnectionDetails::GetPassword()
{
	return this->Password;
}

string ConnectionDetails::GetDatabase()
{
	return this->Database;
}