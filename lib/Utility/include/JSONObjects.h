#ifndef ALTERSPACE_JSONOBJECTS_H
#define ALTERSPACE_JSONOBJECTS_H

#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <Object.h>

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
     * Pre-Condition: Name of desired property, and indexes for where to retrieve its values from JSON
     *
     * Post-Condition: Returns a list of property values
    */
    inline std::vector<std::string> getArray(int iObj, json &j, const std::string &property) {
        std::vector<std::string> values{};

        for (const auto& str : j[iObj][property]) {
            values.push_back(str);
        }
        return values;
    }

    static unsigned int getLengthStrArr(const std::vector<std::string> &strArr) {

        unsigned int length = 0;

        for (const auto& str : strArr) {
            length += str.length();
        }
        return length;
    }

    /*
     * Concatenate strings from an array
     *
     * Pre-Condition: Name of desired property, and indexes for where to retrieve its values from JSON
     *
     * Post-Condition: Returns a string of property values
    */
    inline std::string getStrFromArray(int iObj, json &j, const std::string &property) {

        // Preallocate expected string length, to avoid reallocation & get cache locality
        unsigned int length = getLengthStrArr(j[iObj][property]);
        std::string combinedStr = std::string();
        combinedStr.reserve(length);

        for (const auto& str : j[iObj][property]) {
            combinedStr += str;
        }
        return combinedStr;
    }

    /*
     * Read in the value for a specified key
     *
     * Pre-Condition: Name of key to search for, and indexes for where to retrieve its value from JSON
     *
     * Post-Condition: Returns the key's corresponding value
    */
    inline std::string getValue(int iObj, json &j, const std::string &key) {
        std::string value = std::string();

        value += j[iObj][key];

        return value;
    }

    /*
     * Read in a list of key-value pairs for an item's specified property
     *
     * Pre-Condition: Name of desired property, and indexes for where to retrieve its values from JSON
     *
     * Post-Condition: Returns a list of key-value pairs
    */
    inline std::unordered_map<std::string, std::string> getPairs(int iObj, json &j, const std::string &property) {
        std::unordered_map<std::string, std::string> pairs{};
        int numObjects = j[iObj][property].size();

        for (const auto pair : j[iObj][property].items()) {
            pairs.insert(std::pair<std::string, std::string>(pair.key(), pair.value()));
        }
        return pairs;
    }

    /*
     * Read in a list of values for an item's specified property
     *
     * Pre-Condition: Name of desired (nested) property, and indexes for where to retrieve its values from JSON
     *
     * Post-Condition: Returns a list of property values
    */
    inline std::vector<std::string> getNestedArray(int iObj, int iSubObj, json &j, const std::string &property, const std::string &subproperty) {
        std::vector<std::string> values{};

        for (const auto& str : j[iObj][property][iSubObj][subproperty]) {
            values.push_back(str);
        }
        return values;
    }

    // /*
    //  * Read in a list of objects from a specified JSON file
    //  *
    //  * Pre-Condition: Name of file to parse
    //  *
    //  * Post-Condition: Returns a list of objects
    // */
    // static std::vector<Object> getObjects(const std::string &name) {
    //     json j = setupRead(name);
    //     std::vector<Object> objects{};

    //     int numObjects = j["OBJECTS"].size();
    //     j = j["OBJECTS"];

    //     for (unsigned int i = 0; i < numObjects; i++) {
    //         Object obj(j[i]["id"].get<unsigned int>(),
    //                    getStrFromArray(i, j, "keywords"),
    //                    getPairs(i, j, "abilities"),
    //                    getArray(i, j, "keywords"),
    //                    getValue(i, j, "shortdesc"),
    //                    getArray(i, j, "longdesc"),
    //                    getNestedArray(i, 0, j, "extra", "keywords"),
    //                    getNestedArray(i, 0, j, "extra", "desc"));

    //         objects.push_back(obj);
    //     }

    //     return objects;
    // }

}
#endif //ALTERSPACE_JSONOBJECTS_H
