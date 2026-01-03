#include <string>
#include <iostream>
#include "UserConfig.h"

using namespace std;

UserConfig::UserConfig(Json::Value url, Json::Value username, Json::Value password) : Url(url), Username(username), Password(password) {}

string UserConfig::GetUrl() { return Url.asCString(); }
string UserConfig::GetUsername() { return Username.asCString(); }
string UserConfig::GetPassword() { return Password.asCString(); }