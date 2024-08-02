#pragma once
#include "json/json.h"

class UserConfig
{
private:
	Json::Value Url, Username, Password;

public:
	UserConfig(Json::Value url, Json::Value username, Json::Value password);
	Json::Value GetUrl();
	Json::Value GetUsername();
	Json::Value GetPassword();
};