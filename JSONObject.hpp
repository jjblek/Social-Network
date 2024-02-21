//
// Created by Justin on 9/16/2022.
//

#ifndef PROJECT1_315_JSONOBJECT_HPP
#define PROJECT1_315_JSONOBJECT_HPP

#include "JSONPair.hpp"

/**
 * JSONObject - An array of JSON data (JSONPair.hpp)
 *  consists of an enclosing brace ( { )
 *  followed by comma separated JSON data (JSONPair.hpp),
 *  escaped by a closing brace ( } )
 *
 * Dependent - JSONEntity.hpp
 */

class JSONObject {
public:
    // DEFAULT CONSTRUCTOR
    JSONObject();

    // ADD PAIR TO OBJECT
    void addPair(JSONPair &pair);

    // RETURN THIS OBJECT (ARRAY OF KEY VALUE PAIRS)
    const std::vector<JSONPair> &getObject() const;

    // GET THIS PAIR
    JSONPair* getJSONData(const std::string& key);

    // RETURN NUMBER OF PAIRS IN OBJECT
    size_t size();

    // IS THE OBJECT EMPTY?
    bool empty();

    // GET A NUMBER VALUE BY KEY
    double getNumberValue(const std::string&);
    double getNumberValueRecursively(const std::string&);
    double getNumberValueRecursively(const std::string&, int);

    // GET A STRING VALUE BY KEY
    std::string getStringValue(const std::string&);
    std::vector<std::string> getArrayValue(const std::string&);

    // PRINTERS
    void print();
    void printInJSON(int numSpaces);

private:
    // an object is an array of JSON pairs (JSONPair.hpp)
    std::vector<JSONPair> _object;



};

#endif //PROJECT1_315_JSONOBJECT_HPP
