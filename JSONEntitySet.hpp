//
// Created by Justin on 9/16/2022.
//

#ifndef PROJECT1_315_JSONENTITYSET_HPP
#define PROJECT1_315_JSONENTITYSET_HPP

#include "JSONEntity.hpp"

/**
 * JSONEntitySet - A JSONEntitySet represents the entire JSON file
 * Represented as an array of json entities (JSONEntity.hpp)
 *  consists of an enclosing brace ( { )
 *  containing comma separated json entities (JSONEntity.hpp)
 *  escaped by a closing brace ( } )
 *
 * For Example, a JSONEntitySet could consist of:
 *  Multiple 'users' entities (users1, users2, etc.) holding user objects
 *  As well as an 'admin' entity holding admin objects
 *
 *  Used in class - JSONParser.hpp
 */

class JSONEntitySet {
public:
    // DEFAULT CONSTRUCTOR
    JSONEntitySet();

    // ADD ENTITY TO ENTITY SET
    void addEntity(JSONEntity &);

    // RETURN ENTITY SET
    std::vector<JSONEntity> getEntitySet();

    // SIZE
    size_t size();
    bool empty();

    // PRINTERS
    void print();
    void printInJSON(int numSpaces);

private:
    // an entity set is an array of JSON entities (JSONEntity.hpp)
    std::vector<JSONEntity> _entitySet;
};

#endif //PROJECT1_315_JSONENTITYSET_HPP
