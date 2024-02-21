//
// Created by Justin on 9/16/2022.
//

#include "JSONTokenizer.hpp"

/**
 * CONSTRUCTOR
 * @param inputFile: input to tokenize
 */
JSONTokenizer::JSONTokenizer(const std::string &inputFile):
    inputFileName{inputFile} {
        inputStream.open(inputFile, std::ios::in);
    }

/**
 * getToken - Demarcate/classify section of input
 * Combined accessor - get and set token
 * @return JSONToken
 */
JSONToken JSONTokenizer::getToken() {

    JSONToken token; // initialize token

    if (!inputStream.is_open()) {
        std::cout << "Error: input stream from "
            << inputFileName
            << " is not open. Terminating...\n";
        exit(4);
    }

    char c;
    inputStream >> c;

    if (!inputStream.good()) {
        std::cout << "Error: input stream from "
                  << inputFileName
                  << " is not good. Terminating...\n";
        exit(1);
    }

    // eof case
    if (inputStream.eof()) {
        token.endOfFile() = true;
        return token;
    }

    // number case
    else if (isdigit(c)) {
        inputStream.putback(c); // put it back
        double v;               // initialize double to store attribute value
        inputStream >> v;       // load double
        token.setNumber(v);     // set token to double 'v'
    }

    // string case
    else if (c == '"') {
        std::string s;  // initialize string to store quote
        inputStream.get(c); // get character after starting quotation
        while (c != '"') {  // while ending quotation is not found
            s += c;             // load string
            inputStream.get(c); // get character
        }
        token.setString(s);     // set token to string 's'
    }

    // array/open bracket case
    else if (c == '[') {

        inputStream.get(c);

        // if array is found
        if (c == '"' || c == ']') {

            std::vector<std::string> arr;

            // while the array has not ended
            while (c != ']') {
                std::string str;
                inputStream.get(c); // get character after starting quotation
                while (c != '"') {  // while ending quotation is not found
                    str += c;           // load string
                    inputStream.get(c); // get character
                }
                arr.push_back(str);
                inputStream.get(c);
                if (c == ',') inputStream.get(c);
            }

            token.setArray(arr); // set token to vector 'arr'

        } else { // token is not an array, set token to bracket
            inputStream.putback(c);
            token.setOpenBracket();
        }
    }

    // other expected token cases
    else if (c == '{') token.setOpenBrace();
    else if (c == ':') token.setColon();
    else if (c == '}') token.setClosedBrace();
    else if (c == ']') token.setClosedBracket();
    else if (c == ',') token.setComma();
    else { // an unknown character is found
        std::cout << "Error: Unexpected character in input: " << c;
        token.isUnknown() = true;
        exit(5);
    }

    return token;
}