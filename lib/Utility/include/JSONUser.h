#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <User.h>
#include <boost/filesystem.hpp>

#ifndef ALTERSPACE_JSONUSER_H
#define ALTERSPACE_JSONUSER_H
namespace JSONUser {

    using json = nlohmann::json;
    using jsonf = nlohmann::json;

    const std::string FILE_PATH = "./DataFiles/Users/";
    const std::string EXTENSION = ".json";
    const std::string USER_NAME = "name";
    const std::string USER_PASSWORD = "password";

    const int INDENT = 4;

    static json setupRead(const std::string &username) {
        std::ifstream ifs(FILE_PATH + username + EXTENSION);
        json j;

        if (ifs.is_open()) {
            j = json::parse(ifs);
        }

        return j;
    }

    static jsonf setupWrite(const std::string &username) {
        if(! boost::filesystem::exists(FILE_PATH)) {
            boost::filesystem::create_directory(FILE_PATH);
        }
        std::ofstream file(FILE_PATH + username + EXTENSION);
        jsonf jsonfile;

        if (file.is_open()) {
            file << "{\n\n}";
            file.close();
            std::ifstream ifs(FILE_PATH + username + EXTENSION);
            jsonfile = jsonf::parse(ifs);
        }

        return jsonfile;
    }

    static void writeToFile(const std::string &username, jsonf jsonfile) {
        std::ofstream file(FILE_PATH + username + EXTENSION);
        file << jsonfile.dump(INDENT);
        file.close();
    }

    static bool doesFileExist(const std::string &username) {
        std::string fileName = FILE_PATH + username + EXTENSION;
        std::ifstream f(fileName);
        return f.good();
    }

    static User getUser(const std::string &username) {
        json j = setupRead(username);
        User user(j[USER_NAME].get<std::string>(), j[USER_PASSWORD].get<long int>());
        return user;
    }

    static void createNewUser(const std::string &username, size_t hashedPassword) {
        User user(username, hashedPassword);

        jsonf jsonfile = setupWrite(user.getusername());

        jsonfile.push_back(jsonf::object_t::value_type(USER_NAME, user.getusername()));
        jsonfile.push_back(
                jsonf::object_t::value_type(USER_PASSWORD, user.getHashedPassword()));

        writeToFile(user.getusername(), jsonfile);
    }

}
#endif //ALTERSPACE_JSONUSER_H
