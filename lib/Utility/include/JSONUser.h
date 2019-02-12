
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "json.hpp"
#include <User.h>

#ifndef ALTERSPACE_JSONUSER_H
#define ALTERSPACE_JSONUSER_H
namespace JSONUser {

    namespace {
        using json = nlohmann::json;
        json j;

        using jsonf = nlohmann::json;
        jsonf jsonfile;

        const std::string FILE_PATH = "../DataFiles/Users/";

        const std::string EXTENSION = ".json";

        void setupRead(const std::string &username) {
            std::ifstream ifs(FILE_PATH + username + EXTENSION);
            j = json::parse(ifs);
        }

        void setupWrite(const std::string &username) {
            std::ofstream file(FILE_PATH + username + EXTENSION);
            file << "{\n\n}";
            file.close();
            std::ifstream ifs(FILE_PATH + username + EXTENSION);
            jsonfile = jsonf::parse(ifs);
        }

        void writeToFile(const std::string &username) {
            std::ofstream file(FILE_PATH + username + EXTENSION);
            file << jsonfile.dump(4);
            file.close();
        }
    }


    bool isFileExists(const std::string &username) {
        std::string fileName = FILE_PATH + username + EXTENSION;
        std::ifstream f(fileName.c_str());
        return f.good();
    }

    // TODO make sure to add any other attributes as well
    static User getUser(const std::string &username) {
        setupRead(username);
        User user(j["name"].get<std::string>(), j["password"].get<long int>());
        return user;

    }

    static void createNewUser(const std::string &username, size_t hashedPassword) {
        User user(username,hashedPassword);

        setupWrite(user.getusername());

        jsonfile.push_back(jsonf::object_t::value_type("name", user.getusername()));
        jsonfile.push_back(
                jsonf::object_t::value_type("password", user.getHashedPassword()));

        writeToFile(user.getusername());
    }


}
#endif //ALTERSPACE_JSONUSER_H
