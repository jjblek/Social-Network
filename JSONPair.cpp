//
// Created by Justin on 9/16/2022.
//

#include "JSONPair.hpp"

// construct a pair: string, string
JSONPair::JSONPair(const std::string &attributeName, const std::string &attributeValue) {
    _name = attributeName;
    _stringValue = attributeValue;
    _isString = true;
}

// construct a pair: string, double
JSONPair::JSONPair(const std::string &attributeName, double attributeValue) {
    _name = attributeName;
    _numberValue = attributeValue;
    _isNumber = true;
}

// construct a pair: string, array
JSONPair::JSONPair(const std::string &attributeName, const std::vector<std::string> &array) {
    _name = attributeName;
    _arrayValue = array;
    _isArray = true;
}

// getters
double JSONPair::getValueNumber() const { return _numberValue; }
const std::string &JSONPair::getValueString() const { return _stringValue; }
const std::string &JSONPair::getName() const { return _name; }
const std::vector<std::string> &JSONPair::getValueArray() const { return _arrayValue; }

// returns true if the attribute value is a double
bool JSONPair::isDouble() const { return _isNumber; }

// returns true if the attribute value is a string
bool JSONPair::isString() const { return _isString; }

// returns true if the attribute value is a string
bool JSONPair::isArray() const { return _isArray; }

// print pair without formatting -- debug
void JSONPair::print() {
    std::cout << _name << ": ";
    if (_isNumber) std::cout << std::setprecision(15) << _numberValue;
    else if (_isString) std::cout << _stringValue;
    else if (_isArray) {
        for (int i = 0; i < _arrayValue.size(); i++) {
            if (i == _arrayValue.size()-1) std::cout << _arrayValue[i];
            else std::cout << _arrayValue[i] << ",";
        }
    }
}

// print pair in JSON format
void JSONPair::printInJSON(int numSpaces) {
    std::cout << std::setw(numSpaces) << "\"" << _name << "\" : ";
    if (_isNumber) std::cout << std::fixed << std::setprecision(4) << _numberValue;
    else if (_isString) std::cout << "\"" << _stringValue << "\"";
    else if (_isArray) {
        std::cout << "[";
        for (int i = 0; i < _arrayValue.size(); i++) {
            if (i == _arrayValue.size()-1) std::cout << _arrayValue[i];
            else std::cout << _arrayValue[i] << ",";
        }
        std::cout << "]";
    }
}

