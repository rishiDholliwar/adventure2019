
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

        std::string extension = ".json";

        void setupRead(std::string username) {
            std::ifstream ifs(FILE_PATH + username + extension);
            j = json::parse(ifs);
        }

        void setupWrite(std::string username) {
            std::ofstream file(FILE_PATH + username + extension);
            file << "{\n\n}";
            file.close();
            std::ifstream ifs(FILE_PATH + username + extension);
            jsonfile = jsonf::parse(ifs);
        }

        void writeToFile(std::string username) {
            std::ofstream file(FILE_PATH + username + extension);
            file << jsonfile.dump(4);
            file.close();
        }


    }


//TODO make sure to add any other attributes as well

    bool isFileExists(std::string username) {
        std::string fileName = FILE_PATH + username + extension;
        std::ifstream f(fileName.c_str());
        return f.good();
    }

    static User getUser(std::string username) {
        setupRead(username);
        User user(j["name"].get<std::string>(), j["password"].get<long int>());
        return user;

    }

    static void createNewUser(User user) {
        std::cout << " create user: " << user.getusername() << std::endl;
        setupWrite(user.getusername());
        jsonfile.push_back(jsonf::object_t::value_type("name", user.getusername()));
        jsonfile.push_back(
                jsonf::object_t::value_type("password", user.getHashedPassword()));

        writeToFile(user.getusername());
    }

    static void createNewUser(std::string username, size_t hashedPassword) {
        User user(username,hashedPassword);
        std::cout << " create user: " << user.getusername() << std::endl;
        setupWrite(user.getusername());
        jsonfile.push_back(jsonf::object_t::value_type("name", user.getusername()));
        jsonfile.push_back(
                jsonf::object_t::value_type("password", user.getHashedPassword()));

        writeToFile(user.getusername());
    }


}
#endif //ALTERSPACE_JSONUSER_H
