#pragma once
#include <string> 

int webServerCreate(int n);
float* getStanza(std::string buf);
void stanzaLog(std::string buf);
int connection();
void resetLog();
