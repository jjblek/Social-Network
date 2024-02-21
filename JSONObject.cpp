//
// Created by Justin on 9/16/2022.
//

#include "JSONObject.hpp"

JSONObject::JSONObject() : _object() {}

void JSONObject::addPair(JSONPair &pair) {

    _object.push_back(pair);
    // _object.insert({pair.attributeName(),std::make_pair(pair.stringValue(),pair.numberValue())});
}

// return size (number of pairs in an _object)
size_t JSONObject::size() { return _object.size(); }
bool JSONObject::empty() { return _object.empty(); }


// accessor function helper -- given a key return its string value
std::string JSONObject::getStringValue(const std::string& key) {
    for (auto & pair : _object) {
        if (pair.getName() == key) {
            return pair.getValueString();
        }
    }
    return "";
}

std::vector<std::string> JSONObject::getArrayValue(const std::string& key) {

    for (auto & pair : _object) {
        if (pair.getName() == key) {
            return pair.getValueArray();
        }
    }
    return {};
}

// accessor function helper -- given a key return its number value
double JSONObject::getNumberValue(const std::string& key) {
    for (auto & pair : _object) {
        if (pair.getName() == key) {
            return pair.getValueNumber();
        }
    }
    return 0;
}

// accessor function helper -- given a key return its number value recursively
double JSONObject::getNumberValueRecursively(const std::string &key) {
    return getNumberValueRecursively(key, int(_object.size()) - 1);
}

// recursive helper function -- getNumberValueRecursively
double JSONObject::getNumberValueRecursively(const std::string &key, int n) {
    if (_object.at(n).getName() == key) {
        return _object.at(n).getValueNumber();
    }
    else if (n == 0) return 0;
    return getNumberValueRecursively(key, n - 1);
}

// print _object -- debug
void JSONObject::print() {

    for (auto & pair : _object) {
        pair.print();
        std::cout << "\n";
    }
    std::cout << std::endl;
}

// print _object in JSON format
void JSONObject::printInJSON(int numSpaces) {
    // an instance within a set starts with an open brace
    std::cout << std::setw(numSpaces) << "{" << "\n";
    for (int i = 0; i < getObject().size(); i++) {
        if (i == size() - 1) { // if index is at last attribute
            _object.at(i).printInJSON(numSpaces * 2);
            std::cout << "\n";     // do not print a comma
        } else { // else index is not at last attribute
            _object.at(i).printInJSON(numSpaces * 2);
            std::cout << "," << "\n"; // print a comma
        }
    }
    // an instance within a set ends with a closed brace
    std::cout << std::setw(numSpaces) << "}";
}

const std::vector<JSONPair> &JSONObject::getObject() const {
    return _object;
}

JSONPair* JSONObject::getJSONData(const std::string& key) {
    for (auto & data : _object) {
        if (key == data.getName()) {
            return &data;
        }
    }
    return nullptr;
}
