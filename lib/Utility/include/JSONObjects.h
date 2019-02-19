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

    const std::string FILE_PATH = "./DataFiles/";
    const std::string EXTENSION = ".json";

    static json setupRead(const std::string &name) {
        std::ifstream ifs(FILE_PATH + name + EXTENSION);
        json j;

        if (ifs.is_open()) {
            j = json::parse(ifs);
        }

        return j;
    }

    static bool fileExists(const std::string &name) {
        std::string fileName = FILE_PATH + name + EXTENSION;
        std::ifstream f(fileName);
        return f.good();
    }

    /*
     * Read in a list of values for an item's specified property
     *
     * Pre-Condition: Name of desired property, and an indexes for where to retrieve its values from JSON
     *
     * Post-Condition: Returns a list of property values
    */
    inline std::vector<std::string> getArray(int iObj, json j, std::string property) {
        std::vector<std::string> values{};

        for (auto str : j[iObj][property].items()) {
            values.push_back(str.value());
        }

        // int numValues = j[iObj][property].size();

        // for (unsigned int i = 0; i < numValues; i++) {
        //     values.push_back(j[iObj][property][i]);
        // }

        return values;
    }

    /*
     * Read in a list of key-value pairs for an item's specified property
     *
     * Pre-Condition: Name of desired property, and an indexes for where to retrieve its values from JSON
     *
     * Post-Condition: Returns a list of key-value pairs
    */
    inline std::unordered_map<std::string, std::string> getPairs(int iObj, json j, std::string property) {
        std::unordered_map<std::string, std::string> pairs{};

        for (auto pair : j[iObj][property].items()) {
            pairs.insert(std::pair<std::string, std::string>(pair.key(), pair.value()));
        }
    }

    /*
     * Read in a list of values for an item's specified property
     *
     * Pre-Condition: Name of desired (nested) property, and an indexes for where to retrieve its values from JSON
     *
     * Post-Condition: Returns a list of property values
    */
    inline std::vector<std::string> getNestedArray(int iObj, json j, std::string arr, std::string subarr) {
        std::vector<std::string> values{};

        for (auto obj : j[iObj][arr].items()) {
            for (auto str : j[iObj][arr][subarr]) {
                values.push_back(str.key());
            }
        }

        //int sizeArr = j[iObj][arr].size();
        //
        // for (unsigned int iArr = 0; iArr < sizeArr; iArr++) {
        //     int sizeSubarray = j[iObj][property][iArr][subproperty].size();

        //     for (unsigned int iSubarr = 0; iSubarr < sizeSubarray; iSubarr++) {
        //         values.push_back(j[iObj][property][iArr][subproperty][iSubarr].get<std::string>());
        //     }
        // }
        return values;
    }

    /*
     * Concatenate strings from an array
     *
     * Pre-Condition: Name of desired property, and an indexes for where to retrieve its values from JSON
     *
     * Post-Condition: Returns a string of property values
    */
    inline std::string getStrFromArray(int iObj, json j, std::string property) {
        std::string combinedStr = std::string();

        for (auto str : j[iObj][property].items()) {
            combinedStr += str.key();
        }

        // int numValues = j[iObj][property].size();

        // for (unsigned int i = 0; i < numValues; i++) {
        //     combinedStr += j[iObj][property][i];
        // }
        return combinedStr;
    }

    /*
     * Read in a list of objects from a specified JSON file
     *
     * Pre-Condition: Name of file to parse
     *
     * Post-Condition: Returns a list of objects
    */
    static std::vector<Object> getObjects(const std::string &name) {
        json j = setupRead(name);
        std::cout << "read json" << std::endl;
        std::vector<Object> objects{};
        std::cout << "initialized object vector" << std::endl;

        int numObjects = j["OBJECTS"].size();
        std::cout << "number of objects: " << numObjects << std::endl;
        j = j["OBJECTS"];

        for (unsigned int i = 0; i < numObjects; i++) {
            Object obj(j[i]["id"].get<unsigned int>(),
                       getStrFromArray(i, j, "keywords"),
                       getPairs(i, j, "abilities"),
                       getArray(i, j, "keywords"),
                       j[i]["shortdesc"],
                       getArray(i, j, "longdesc"),
                       getNestedArray(i, j, "extra", "keywords"),
                       getNestedArray(i, j, "extra", "desc"));
            std::cout << "Created object " << i << std::endl;

            objects.push_back(obj);
        }

        return objects;
    }

}
#endif //ALTERSPACE_JSONOBJECTS_H
