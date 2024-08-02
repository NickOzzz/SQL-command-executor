#include <string>
#include <iostream>
#include "UserConfig.h"

using namespace std;

UserConfig::UserConfig(Json::Value url, Json::Value username, Json::Value password) : Url(url), Username(username), Password(password) {}

Json::Value UserConfig::GetUrl() { return Url.asCString(); }
Json::Value UserConfig::GetUsername() { return Username.asCString(); }
Json::Value UserConfig::GetPassword() { return Password.asCString(); }