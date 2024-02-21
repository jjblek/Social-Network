//
// Created by Justin on 9/16/2022.
//

#include "User.hpp"

/** DEFAULT CONSTRUCTOR **/
User::User(): _empty{true} {}

/**
 * PARAMETERIZED CONSTRUCTOR
 * @param userObject: JSONObject
 */
User::User(const JSONObject& userObject) {

    /** TIME COMPLEXITY: O(N), N = user.size()
    *   AMORTIZED: O(1),
    *       A USER IS EXPECTED TO ONLY HAVE 5 ATTRIBUTES **/
    for (auto & attribute: userObject.getObject()) {

        std::string key = attribute.getName();

        if (attribute.isString()) {

            std::string value = attribute.getValueString();

            if (key == "id_str") {
                _id = attribute.getValueString();
                continue;
            }

            else if (key == "name") {
                _name = attribute.getValueString();
                continue;
            }

            else if (key == "location") {
                _location = attribute.getValueString();
                continue;
            }

            else if (key == "pic_url") {
                _pic_url = attribute.getValueString();
                continue;
            }
            else {
                std::cout << "Invalid User Data Key: \""
                          << attribute.getName() << "\" : "
                    << std::endl;
                exit(1);
            }
        }

        else if (attribute.isArray() && key == "follows") {
            _followIds = attribute.getValueArray();
            continue;
        }

        else if (attribute.isDouble()) {
            std::cout << "Invalid User Data Value: \""
                      << attribute.getName() << "\" : "
                      << attribute.getValueNumber() << std::endl;
            exit(1);
        }

        else {
            std::cout << "Invalid User Data Value: \""
                << attribute.getName()
                << "\"" << std::endl;
            exit(1);
        }

    }
    _empty = false;
}

/**
 * ADD follower
 * @param first : follower id
 * @param second: follower name
 */
void User::addFollower(const int& first, const std::string& second) {
    std::pair<int, std::string> follower(first, second);
    _followers.push_back(follower);
}

/**
 * ADD follow
 * @param first : follow id
 * @param second: follow name
 */
void User::addFollow(const int& first, const std::string& second) {
    std::pair<int, std::string> follow(first, second);
    _follows.push_back(follow);
}

/**
 * ADD mutual
 * @param first : mutual id
 * @param second: mutual name
 */
void User::addMutual(const int& first, const std::string& second) {
    std::pair<int, std::string> mutual(first, second);
    _mutuals.push_back(mutual);
}

/**
 * GENERATE HTML
 * @param withCSS: generate CSS, true or false
 */
void User::generateHTML(bool withCSS) {
    // set default pic url
    std::string default_pic_url = "https://i1.wp.com/researchictafrica.net/wp/wp-content/uploads/2016/10/default-profile-pic.jpg?ssl=1";

    std::fstream file;

    file.open("SocialNetwork/user" + _id + ".html", std::ios::out);

    assert(file);

    file <<
        "<!DOCTYPE html>\n<html lang=\"en\">\n"
        "<head>\n" << (withCSS ?
        "\t<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />\n" : "") <<
        "\t<title>" << _name << " User</title>\n"
        "</head>\n"
        "<body style=\"margin: 0\">\n"
        "\t<nav class=\"navbar\">\n"
        "\t\t<a href=\"index.html\"><b>Home</b></a>\n"
        "\t\t<h1>Social Network</h1>\n"
        "\t</nav>\n"
        "\t<div class=\"user\">\n"
        "\t\t<div class=\"userInfo\" style=\"display: flex; align-items: center\">\n"
        "\t\t\t<span class=\"avatar\">\n"
        "\t\t\t\t<img alt=\"User pic\"\n"
        "\t\t\t\t\tsrc=\"" << (_pic_url.empty() ? default_pic_url : _pic_url) << "\"\n"
        "\t\t\t\t/>\n"
        "\t\t\t</span>\n"
        "\t\t\t<h2>\n\t\t\t\t<b id=\"name\">" << _name << "</b>\n"
        << (_location.empty() ? "" :
        "\t\t\t\t<span id=\"location\">in " + _location + "</span>\n") <<
        "\t\t\t</h2>\n"
        "\t\t</div>\n"
        "\t\t<div class=\"relations\">\n"
        "\t\t\t<div id=\"following\">\n"
        "\t\t\t\t<h2>Following:\n"
        "\t\t\t\t\t<span class=\"value\" style=\"font-size: inherit\">\n"
        "\t\t\t\t\t\t" << _follows.size() <<
        "\n\t\t\t\t\t</span>\n"
        "\t\t\t\t</h2>\n"
        << generateList(_follows) <<
        "\t\t\t</div>\n"
        "\t\t\t<div id=\"followers\">\n"
        "\t\t\t\t<h2>Followers:\n"
        "\t\t\t\t\t<span class=\"value\" style=\"font-size: inherit\">\n"
        "\t\t\t\t\t\t" << _followers.size() <<
        "\n\t\t\t\t\t</span>\n"
        "\t\t\t\t</h2>\n"
        << generateList(_followers) <<
        "\t\t\t</div>\n"
        "\t\t\t<div id=\"mutuals\">\n"
        "\t\t\t\t<h2>Mutuals:\n"
        "\t\t\t\t\t<span class=\"value\" style=\"font-size: inherit\">\n"
        "\t\t\t\t\t\t" << _mutuals.size() <<
        "\n\t\t\t\t\t</span>\n"
        "\t\t\t\t</h2>\n"
        << generateList(_mutuals) <<
        "\t\t\t</div>\n"
        "\t\t</div>\n"
        "\t</div>\n"
        "</body>\n"
        "\n"
        "</html>";

    file.close();
}

/**
 * GENERATE UNORDERED LIST
 * @param relations: array of relations (follows, followers, mutuals)
 * @return html unordered list as a string
 */
std::string User::generateList(const std::vector<std::pair<int, std::string>>& relations) {
    std::ostringstream element;
    if (relations.empty()) {
        element << "<p>None</p>";
    } else {
        element << "\t\t\t\t<ul>\n";
        for (auto & relation : relations) {
            element <<
                    "\t\t\t\t\t<li><a href=\"user"
                    << relation.first << ".html\">"
                    << relation.second << "</a></li>\n";
        }
        element << "\t\t\t\t</ul>\n";

    }
    return element.str();
}
