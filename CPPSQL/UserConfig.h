#pragma once
#include "json/json.h"
#include <string>

using namespace std;

class UserConfig
{
private:
	Json::Value Url, Username, Password;

public:
	UserConfig(Json::Value url, Json::Value username, Json::Value password);
	string GetUrl();
	string GetUsername();
	string GetPassword();
};