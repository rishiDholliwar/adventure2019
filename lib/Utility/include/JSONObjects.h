#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <Object.h>

#ifndef ALTERSPACE_JSONOBJECTS_H
#define ALTERSPACE_JSONOBJECTS_H
namespace JSONObjects {

    using json = nlohmann::json;
    using jsonf = nlohmann::json;

    const std::string FILE_PATH = "../DataFiles/";
    const std::string EXTENSION = ".json";

    static json setupRead(const std::string &name) {
        std::ifstream ifs(FILE_PATH + name + EXTENSION);
        json j;

        if (ifs.is_open()) {
            j = json::parse(ifs);
        }

        return j;
    }

    static bool doesFileExist(const std::string &name) {
        std::string fileName = FILE_PATH + name + EXTENSION;
        std::ifstream f(fileName);
        return f.good();
    }

    std::vector<std::string> getArray(int i, json j, std::string arrayName) {
        std::vector<std::string> vec;
        int size = j[i][arrayName].size();

        for (unsigned int k = 0; k < size; k++) {
            vec.push_back(j[i][arrayName][k]);
        }

        return vec;
    }

    std::vector<std::string> getNestedStringArray(int i, json j, std::string obj, std::string field) {
        std::vector<std::string> vec;
        int size = j[i][obj].size();

        for (unsigned int k = 0; k < size; k++) {
            int size2 = j[i][obj][k][field].size();

            for (unsigned int k2 = 0; k2 < size2; k2++) {
                vec.push_back(j[i][obj][k][field][k2].get<std::string>());
            }
        }

        return vec;
    }

    static std::vector<Object> getObjects(const std::string &name) {
        json j = setupRead(name);
        std::vector<Object> vec;

        int size = j["OBJECTS"].size();
        j = j["OBJECTS"];

        for (unsigned int i = 0; i < size; i++) {
            Object obj(j[i]["id"].get<unsigned int>(),
                       getArray(i, j, "keywords"),
                       j[i]["shortdesc"],
                       getArray(i, j, "longdesc"),
                       getNestedStringArray(i, j, "extra", "keywords"),
                       getNestedStringArray(i, j, "extra", "desc"));

            vec.push_back(obj);
        }

        return vec;
    }

}
#endif //ALTERSPACE_JSONOBJECTS_H