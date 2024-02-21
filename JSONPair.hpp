//
// Created by Justin on 9/16/2022.
//

#ifndef PROJECT1_315_JSONPAIR_HPP
#define PROJECT1_315_JSONPAIR_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

/**
 * JSONPair - A name/value pair ("name" : value), the innermost JSON structure
 *  A name/value pair consists of a field name, followed by a colon, followed by a value
 *
 * In JSON, values must be one of the following data types:
 *  @string, @number, @array,
 *  TODO: @object (JSON _object)
 *  TODO: @bool
 *  TODO: @null
 * this class limits the data types of values to double, string, array.
 */

class JSONPair {
public:
    // DEFAULT CONSTRUCTOR
    JSONPair() = default;

    // PARAMETERIZED CONSTRUCTOR: DOUBLE
    JSONPair(const std::string &attributeName, double attributeValue);

    // PARAMETERIZED CONSTRUCTOR: STRING
    JSONPair(const std::string &attributeName, const std::string &attributeValue);

    // PARAMETERIZED CONSTRUCTOR: ARRAY
    JSONPair(const std::string &attributeName, const std::vector<std::string> &attributeValue);

    bool isString() const;  // is the datatype of the value a STRING?
    bool isArray() const;   // is the datatype of the value an ARRAY?
    bool isDouble() const;  // is the datatype of the value a DOUBLE?

    const std::string &getName() const;                     // get key  : STRING
    const std::string &getValueString() const;              // get value: STRING
    const std::vector<std::string> &getValueArray() const;  // get value: ARRAY
    double getValueNumber() const;                          // get value: DOUBLE

    // PRINTERS
    void print();
    void printInJSON(int numSpaces);

private:
    std::string _name, _stringValue;
    std::vector<std::string> _arrayValue;
    double _numberValue{};

    bool _isNumber{false}, _isString{false}, _isArray{false};
};

#endif //PROJECT1_315_JSONPAIR_HPP
