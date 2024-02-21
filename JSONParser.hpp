//
// Created by Justin on 9/16/2022.
//

#ifndef PROJECT1_315_JSONPARSER_HPP
#define PROJECT1_315_JSONPARSER_HPP


#include "JSONTokenizer.hpp"
#include "JSONEntitySet.hpp"
#include <cassert>

/**
 * JSONParser - parse JSON files
 *  Usage:
 *      JSONParser jsonParser(nameOfInputFile);
 *      JSONEntitySet sets = jsonParser.parseJSONEntitySet();
 *      sets.printInJSON(numSpaces);
 *
 * JSON Structure:
 *--------------------------------------------------
 *   {                           <- EntitySet Start
 *   "_profiles": [              <- Entity Start
 *       {                       <- Object Start
 *           "name" : "value" ,  <- Data - string
 *           "name" : 5          <- Data - double
 *       },                      <- Object End
 *       {                       <- Object Start
 *           "name" : "value" ,  <- Data - string
 *           "name" : ["1", "2"] <- Data - Array
 *       },                      <- Object End
 *   ]                           <- Entity End
 *   }                           <- EntitySet End
 *--------------------------------------------------
 *
 * Dependent: SocialNetwork.hpp
 */

class JSONParser {
public:
    // CONSTRUCTOR
    explicit JSONParser(const std::string& nameOfInputFile);

    // PARSE JSON
    JSONPair parseJSONData();
    JSONObject parseJSONObject();
    JSONEntity parseJSONEntity();
    JSONEntitySet parseJSONEntitySet();
private:
    JSONTokenizer _tokenizer; // the input file name is used to create an instance of JSONTokenizer
};

#endif //PROJECT1_315_JSONPARSER_HPP
