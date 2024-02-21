//
// Created by Justin on 9/16/2022.
//

#ifndef PROJECT1_315_USER_HPP
#define PROJECT1_315_USER_HPP

#include "JSONObject.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

/**
 * User - a JSONObject with the following attributes, which may be listed in any order
 *  id_str:
 *      an integer represented as a quoted string. Every user is guaranteed to have an id_str.
 *      If you have N users, they will have id_str values of “1” through “N”,
 *      but they will not necessarily appear in the file in that order.
 *  name:
 *      a quoted string. Every user is guaranteed to have a name.
 *  location:
 *      a quoted string. A user may or may not have this attribute.
 *  pic_url:
 *      a URL, as a quoted string. A user may or may not have this attribute.
 *  follows:
 *      a JSON array of integers represented as quoted strings.
 *      This is a list of the id_str values of the people this user follows.
 *      This array may be empty. If it’s not present at all,
 *      you should infer that it’s empty and that this user does not follow anyone.
 *
 * Users will not have any attributes other than those listed above.
 */

class User {
public:
    // DEFAULT CONSTRUCTOR
    User();

    // PARAMETERIZED CONSTRUCTOR: JSONObject
    explicit User(const JSONObject& userObject);

    // GETTERS
    const std::string &getId() const { return _id; }
    const std::string &getName() const { return _name; }
    const std::vector<std::string> &getFollows() const { return _followIds; }

    // ADD RELATIONS
    void addFollower(const int&, const std::string&);
    void addFollow(const int&, const std::string&);
    void addMutual(const int&, const std::string&);

    // HTML PRINTER
    void generateHTML(bool isStyled);

    bool isEmpty() const { return _empty; };

private:
    // CONSTRUCT HTML List
    static std::string generateList(const std::vector<std::pair<int, std::string>>&);

    bool _empty = true;

    std::string
        _id,
        _name,
        _location,
        _pic_url;

    std::vector<std::string> _followIds;

    std::vector<std::pair<int, std::string>>
        _follows,
        _followers,
        _mutuals;
};

#endif //PROJECT1_315_USER_HPP
