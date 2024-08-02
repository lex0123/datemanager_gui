#include"user.h"
std::string fileName="user.txt";
std::unordered_map<std::string, std::string> loadUsers(const std::string& filename) {
    std::unordered_map<std::string, std::string> users;
    std::ifstream infile(filename);
    std::string username, HashPassWd;
    while (infile >> username >> HashPassWd) {
        users[username] = HashPassWd;
    }
    return users;
}
// Function to save users to a file
void saveUser(const std::string& filename, const std::string& username, const std::string& password) {
    std::ofstream outfile(filename, std::ios_base::app);
    std::string HashPassWd;
    picosha2::hash256_hex_string(password,HashPassWd);
    outfile << username <<'\t'<< HashPassWd << std::endl;
}

// Function to register a new user
int registerUser(const std::string& filename,std::string &username,std::string &password) {
    std::unordered_map<std::string, std::string> users = loadUsers(filename);
    if (users.count(username)!=0) return 1;
    if (password.size()<4) return 2;
    saveUser(filename, username, password);
    std::fstream taskFile(username,std::ios_base::app);
    taskFile<<0<<std::endl;
    return 0;
}
// Function to log
bool loginUser(const std::string& filename,const std::string& username,const std::string &password) {
    std::unordered_map<std::string, std::string> users = loadUsers(filename);
    std::string HashPassWd;
    picosha2::hash256_hex_string(password,HashPassWd);
    if (users.find(username) != users.end() && users[username] == HashPassWd) {
        return true;
    } else {
        return false;
    }
}
