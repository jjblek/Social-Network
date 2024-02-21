//
// Created by Justin on 9/16/2022.
//

#ifndef PROJECT1_315_JSONTOKEN_HPP
#define PROJECT1_315_JSONTOKEN_HPP


#include <string>
#include <iostream>
#include <vector>

/**
 * JSONToken - Define a JSON token
 * Valid JSON tokens:
 *  characters: {  [  "  ,  :  ]  }
 *  values: string  double  array
 *
 * Dependent - JSONTokenizer.hpp
 */

class JSONToken {
public:
    // DEFAULT CONSTRUCTOR
    JSONToken():
        _char{'\0'},
        _number{0},
        _isNumber{false},
        _isString{false},
        _isArray{false},
        _isEOF{false},
        _isUnknown{false}
    {}

    // GETTERS
    std::string getString() const { return _string; }
    double getNumber() const { return _number; }
    std::vector<std::string> getArray() const { return _array; }
    bool &isNumber() { return _isNumber; }
    bool isString() const { return _isString; }
    bool &isArray() { return _isArray; }
    bool isComma() const { return _char == ','; }
    bool isColon() const { return _char == ':'; }
    bool isOpenBracket() const { return _char == '['; }
    bool isClosedBracket() const { return _char == ']'; }
    bool isOpenBrace() const { return _char == '{'; }
    bool isClosedBrace() const { return _char == '}'; }
    bool &isUnknown() { return _isUnknown; }
    bool &endOfFile() { return _isEOF; }

    // SETTERS
    void setNumber(double v) {
        _number = v;
        _isNumber = true;
    }
    void setString(const std::string &s) {
        _string = s;
        _isString = true;
    }
    void setArray(const std::vector<std::string> &a){
        _array = a;
        _isArray = true;
    }

    void setComma() { _char = ','; }
    void setColon() { _char = ':'; }
    void setOpenBracket() { _char = '['; }
    void setClosedBracket() { _char = ']'; }
    void setOpenBrace() { _char = '{'; }
    void setClosedBrace() { _char = '}'; }

private:
    char _char;

    std::string _string;
    double _number;
    std::vector<std::string> _array;

    bool _isNumber, _isString, _isArray, _isEOF, _isUnknown;
};

#endif //PROJECT1_315_JSONTOKEN_HPP
