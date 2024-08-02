#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>
#include "picosha2.h"
#include <unordered_map>
#include <iomanip>

std::unordered_map<std::string, std::string> loadUsers(const std::string& filename);
void saveUser(const std::string& filename, const std::string& username, const std::string& password);
int registerUser(const std::string& filename,std::string &username,std::string &password);
bool loginUser(const std::string& filename,const std::string& username,const std::string &password);
//
#endif