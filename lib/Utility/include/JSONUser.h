#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <User.h>

#ifndef ALTERSPACE_JSONUSER_H
#define ALTERSPACE_JSONUSER_H
namespace JSONUser {

    using json = nlohmann::json;
    json j;

    using jsonf = nlohmann::json;
    jsonf jsonfile;

    const std::string FILE_PATH = "../DataFiles/Users/";
    const std::string EXTENSION = ".json";
    const std::string USER_NAME = "name";
    const std::string USER_PASSWORD = "password";

    const int INDENT = 4;

    static void setupRead(const std::string &username) {
        std::ifstream ifs(FILE_PATH + username + EXTENSION);
        if (ifs.is_open()) {
            j = json::parse(ifs);
        }
    }

    static void setupWrite(const std::string &username) {
        std::ofstream file(FILE_PATH + username + EXTENSION);
        if (file.is_open()) {
            file << "{\n\n}";
            file.close();
            std::ifstream ifs(FILE_PATH + username + EXTENSION);
            jsonfile = jsonf::parse(ifs);
        }
    }

    static void writeToFile(const std::string &username) {
        std::ofstream file(FILE_PATH + username + EXTENSION);
        file << jsonfile.dump(INDENT);
        file.close();
    }

    static bool isFileExists(const std::string &username) {
        std::string fileName = FILE_PATH + username + EXTENSION;
        std::ifstream f(fileName);
        return f.good();
    }

    static User getUser(const std::string &username) {
        setupRead(username);
        User user(j[USER_NAME].get<std::string>(), j[USER_PASSWORD].get<long int>());
        return user;
    }

    static void createNewUser(const std::string &username, size_t hashedPassword) {
        User user(username, hashedPassword);

        setupWrite(user.getusername());

        jsonfile.push_back(jsonf::object_t::value_type(USER_NAME, user.getusername()));
        jsonfile.push_back(
                jsonf::object_t::value_type(USER_PASSWORD, user.getHashedPassword()));

        writeToFile(user.getusername());
    }

}
#endif //ALTERSPACE_JSONUSER_H
