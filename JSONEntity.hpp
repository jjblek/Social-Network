//
// Created by Justin on 9/16/2022.
//

#ifndef PROJECT1_315_JSONENTITY_HPP
#define PROJECT1_315_JSONENTITY_HPP

#include "JSONObject.hpp"

/**
 * JSONEntity - An array of JSON objects
 *  has a double quoted name followed by a colon ( "name": )
 *  followed by an enclosing bracket ( [ )
 *  can contain multiple comma separated JSON objects
 *  escaped by a closing bracket ( ] )
 *
 * For example, a JSONEntity 'users' is an array of user objects
 *
 * Dependent - JSONEntitySet.hpp
 */

class JSONEntity {
public: // METHODS
    // DEFAULT CONSTRUCTOR
    JSONEntity();

    // ADD OBJECT TO ENTITY
    void addObject(JSONObject &);

    // ADD PAIR AT OBJECT INDEX
    void addDataAtObject(JSONPair &pair, int index);

    // RETURN ENTITY
    std::vector<JSONObject> getEntity();

    // SIZE & EMPTY
    size_t size();
    bool empty();

    // GET ENTITY NAME
    const std::string &getEntityName() const;

    // SET ENTITY NAME
    void setEntityName(const std::string &entityName);

    // PRINTERS
    void print();
    void printInJSON(int numSpaces);

private:
    std::string _entityName;
    // an entity is an array of JSON objects (JSONObject.hpp)
    std::vector<JSONObject> _entity;
};

#endif //PROJECT1_315_JSONENTITY_HPP
