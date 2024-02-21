//
// Created by Justin on 9/16/2022.
//

#include "JSONEntity.hpp"

JSONEntity::JSONEntity() : _entity() {}

// add an object to an entity
void JSONEntity::addObject(JSONObject &object) {
    _entity.push_back(object);
}

// add a pair to an entity at a specified index
void JSONEntity::addDataAtObject(JSONPair &pair, int index) {
    _entity.at(index).addPair(pair);
}

// return entity
std::vector<JSONObject> JSONEntity::getEntity() {
    return _entity;
}

// return size (number of objects in an entity)
size_t JSONEntity::size() { return _entity.size(); }
bool JSONEntity::empty() { return _entity.empty(); }

// get and set entity name
const std::string &JSONEntity::getEntityName() const { return _entityName; }
void JSONEntity::setEntityName(const std::string &entityName) { _entityName = entityName; }

// print an entity
void JSONEntity::print() {
    std::cout << getEntityName() + ':' << "\n";
    std::cout << "[" << "\n";
    for (auto & instance : _entity) {
        instance.print();
    }
    std::cout << "]" << std::endl;
}

// print an entity in JSON format
void JSONEntity::printInJSON(int numSpaces) {
    std::cout << '"' + getEntityName() + '"' + ": [" << "\n";
    for (int i = 0; i < _entity.size(); i++) {
        if (i == _entity.size() - 1) { // if last _entity instance
            _entity.at(i).printInJSON(numSpaces); // print instance
            std::cout << "\n"; // do not print a comma
        }
        else {
            _entity.at(i).printInJSON(numSpaces); // print instance
            std::cout << "," << "\n"; // print a comma
        }
    }
    std::cout << "]";
}
