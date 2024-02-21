//
// Created by Justin on 9/16/2022.
//

#ifndef PROJECT1_315_JSONTOKENIZER_HPP
#define PROJECT1_315_JSONTOKENIZER_HPP

#include <string>
#include <fstream>

#include "JSONToken.hpp"

/**
 * JSONTokenizer - Demarcate/classify section of input
 *  Using JSONToken to define a token,
 *  JSONTokenizer is a sub-task of JSONParser
 *
 * Dependent - JSONParser.hpp
 */

class JSONTokenizer {
public:
    // CONSTRUCTOR
    explicit JSONTokenizer(const std::string &inputFile);
    // GET AND SET TOKEN
    JSONToken getToken();

private:
    std::string inputFileName;
    std::ifstream inputStream;
};

#endif //PROJECT1_315_JSONTOKENIZER_HPP
