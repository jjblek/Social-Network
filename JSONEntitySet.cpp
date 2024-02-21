//
// Created by Justin on 9/16/2022.
//

#include "JSONEntitySet.hpp"

JSONEntitySet::JSONEntitySet() : _entitySet() {}

void JSONEntitySet::addEntity(JSONEntity &entity) { _entitySet.push_back(entity); }
std::vector<JSONEntity> JSONEntitySet::getEntitySet() { return _entitySet; }

size_t JSONEntitySet::size() { return _entitySet.size(); }
bool JSONEntitySet::empty() { return _entitySet.empty(); }

// print an entity set
void JSONEntitySet::print() {
    std::cout << "{" << "\n";
    for (auto & entity : _entitySet) {
        entity.print();
    }
    std::cout << "}" << std::endl;
}

// print an entity set in JSON format
void JSONEntitySet::printInJSON(int numSpaces) {
    std::cout << "{" << std::endl;
    for (int i = 0; i < _entitySet.size(); i++) {
        if (i == _entitySet.size() - 1) { // if last _entity instance
            _entitySet.at(i).printInJSON(numSpaces); // print instance
            std::cout << "\n"; // do not print a comma
        }
        else {
            _entitySet.at(i).printInJSON(numSpaces); // print instance
            std::cout << "," << "\n"; // print a comma
        }
    }
    std::cout << "}" << std::endl;
}
