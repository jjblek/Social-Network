//
// Created by Justin on 9/16/2022.
//

#include "SocialNetwork.hpp"

/** DEFAULT CONSTRUCTOR **/
SocialNetwork::SocialNetwork(): _userMap() {}


/**
 * PARAMETRIZED CONSTRUCTOR
 * @param inputFile
 */
SocialNetwork::SocialNetwork(const std::string &inputFile) {

    JSONParser jsonParser(inputFile);

    JSONEntitySet set = jsonParser.parseJSONEntitySet();

    /** Traverse the JSONEntitySet to find the 'users' entity
    *   WORST CASE: O(N)
    *       N = JSONEntitySet.size (ENTITIES)
    *   EXPECTED: O(1), ONLY ONE ENTITY IS EXPECTED **/
    for (auto &entity : set.getEntitySet()) {

        assert(entity.getEntityName() == "users");

        // initialize follower matrix
        std::vector<std::vector<bool>> followerMatrix {
                entity.size()+1,
                std::vector<bool>(entity.size()+1, false)
        };

        /** Traverse the JSONEntity and insert users into the profile map
        *   WORST CASE: O(N^2logN), traverse users.size twice & map insertion
        *       M = users.size (USERS)
        *       N = users.size (FOLLOWS)
        *   EXPECTED: O(M*NlogM), M = users.size, N != users.size;
        *       FOLLOWS ARE EXPECTED TO BE SPARSE **/
        for (auto &object : entity.getEntity()) {

            // initialize a user with a JSONObject
            User user(object);
            int currentId = stoi(user.getId());

            // set follower matrix
            for (auto & followId: user.getFollows()) {
                followerMatrix
                .at(stoi(followId))
                .at(currentId)
                .flip();
            }

            // map the newly constructed user O(logN)
            _userMap.insert({currentId, user});

        }

        /** Traverse the profile map to determine user relations
        *   WORST CASE: O(N^2logN), traverse users.size twice & access map
        *       M = users.size (USERS)
        *       N = users.size (FOLLOWS)
        *   EXPECTED: O(M*NlogN), M = users.size, N = != users.size
        *       FOLLOWS ARE EXPECTED TO BE SPARSE **/
        for (auto &user : _userMap) {

            int currentId = user.first;
            User& currentUser = user.second;

            if (currentUser.isEmpty()) continue; // if a user is empty, skip it

            // for each follow: add a follow, a follower, and check if mutual
            for (auto &followId: currentUser.getFollows()) {

                int otherId = stoi(followId);

                if (currentId == otherId) continue;

                User& otherUser = _userMap[otherId];

                currentUser.addFollow(otherId, otherUser.getName());       // ADD FOLLOW
                otherUser.addFollower(currentId, currentUser.getName());   // ADD FOLLOWER
                // map access O(logN)
                if (followerMatrix[currentId][otherId] &&
                    followerMatrix[otherId][currentId])
                    currentUser.addMutual(otherId, otherUser.getName());   // ADD MUTUAL
            }
        }

    }
}


/**
 * open - open the Social Network (index.html)
 *  execute an OS specific open command on index.html
 */
void SocialNetwork::open() {
    // OPEN HTML INDEX FILE IN BROWSER
    #ifdef COMPILED_IN_WINDOWS

    ShellExecute(NULL,"open",
                 "index.html",
                 NULL,DIRECTORY_NAME,
                 SW_SHOWNORMAL);
    #else
        std::string dir = DIRECTORY_NAME;
        std::string command = "xdg-open " + dir + "/index.html";
        system(command.c_str());
    #endif
}


/**
 * createDirectory - make directory for html files
 *  execute an OS specific make directory command
 * @return true if directory exists or is created, false otherwise
 */
bool SocialNetwork::createDirectory() {
    #ifdef COMPILED_IN_WINDOWS
    if (mkdir(DIRECTORY_NAME) == -1) {
        if (errno == EEXIST) return true;
        else return false;
    }

    #else
    if (mkdir(DIRECTORY_NAME, 0777) == -1) {
        if (errno == EEXIST) return true;
        else return false;
    }
    #endif
    return true;
}


/**
 * generateHTML - generate HTML files for Social Network
 * @param withCSS: true to generate CSS, set with program argument
 */
void SocialNetwork::generateHTML(bool withCSS) {

    assert(!empty() && createDirectory());

    if (withCSS) generateCSS();

    std::fstream file;

    std::string dir = DIRECTORY_NAME;

    file.open(dir + "/index.html", std::ios::out);

    assert(file);

    file <<
        "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n"
            << (withCSS ? // link stylesheet
            "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" />\n"
            : "\n") <<
        "<title>My Social Network</title>\n"
        "</head>\n"
        "<body style=\"margin: 0\">\n"
        "\t<nav class=\"navbar\">\n"
        "\t\t<a class=\"active\" href=\"index.html\"><b>Home</b></a>\n"
        "\t\t<h1>Social Network</h1>\n"
        "   </nav>\n"
        "   <div class=\"network\">\n"
        "       <h1>User List:</h1>\n"
        "       <ol>\n";
    // loop users to generate an ordered list of users
    for (auto & user : _userMap) {
        if (user.second.isEmpty()) continue; // skip empty user
        // generate HTML file for ith user
        user.second.generateHTML(withCSS);
        file << "           <li><a href=\"user"
        << user.first << ".html\">"
        << user.second.getName() << "</a></li>\n";
    }

    file <<
        "       </ol>\n"
        "   </div>\n"
        "</body>\n\n"
        "</html>";

    file.close();
}


/**
 * generateCSS - generate a style.css file
 */
void SocialNetwork::generateCSS() {

    std::fstream file;

    std::string dir = DIRECTORY_NAME;
    file.open(dir + "/style.css", std::ios::out);

    assert(file);

    file <<
    "@import url('https://fonts.googleapis.com/css2?family=Quicksand&display=swap');\n"
    "\n"
    ".navbar {\n"
    "    overflow: hidden;\n"
    "    background-color: #2e3136;\n"
    "    position: fixed;\n"
    "    top: 0;\n"
    "    height: 50px;\n"
    "    width: 100%;\n"
    "}\n"
    ".navbar a {\n"
    "    position: fixed;\n"
    "    float: left;\n"
    "    color: #f2f2f2;\n"
    "    text-align: center;\n"
    "    padding: 14px 16px;\n"
    "    text-decoration: none;\n"
    "}\n"
    ".navbar h1 {\n"
    "    text-align: center;\n"
    "    padding-top: 8px;\n"
    "    margin: 0;\n"
    "}\n"
    ".navbar a:hover {\n"
    "    background-color: #7289da;\n"
    "    color: white;\n"
    "}\n"
    ".navbar a.active {\n"
    "    background-color: #7289da;\n"
    "    color: white;\n"
    "}\n"
    "html, body {\n"
    "    height: 100vh;\n"
    "}\n"
    "body {\n"
    "    background-color: #36393e;\n"
    "    display: flex;\n"
    "    justify-content: center;\n"
    "}\n"
    ".network, .user {\n"
    "    display: flex;\n"
    "    flex-direction: column;\n"
    "    align-items: center;\n"
    "    min-height: 100px;\n"
    "    background: #3e4147;\n"
    "    margin: 100px 50px 50px;\n"
    "    padding: 20px;\n"
    "    border-radius: 8px;\n"
    "    overflow: hidden;\n"
    "}\n"
    ".network ::-webkit-scrollbar, .user ::-webkit-scrollbar {\n"
    "    width: 12px;\n"
    "    height: 12px;\n"
    "}\n"
    ".network ::-webkit-scrollbar-track, .user ::-webkit-scrollbar-track {\n"
    "    border-radius: 10px;\n"
    "    background: #36393e;\n"
    "    box-shadow: 0 0 1px 1px #2e3136, inset 0 0 4px rgba(0,0,0,0.3);\n"
    "}\n"
    ".network ::-webkit-scrollbar-thumb, .user ::-webkit-scrollbar-thumb {\n"
    "    border-radius: 10px;\n"
    "    background: #7289da;\n"
    "    box-shadow: inset 0 0 1px 1px #fff;\n"
    "}\n"
    ".network ::-webkit-scrollbar-thumb:hover, .user ::-webkit-scrollbar-thumb:hover {\n"
    "    background: #5c6fb2;\n"
    "}\n"
    ".network ol {\n"
    "    overflow: hidden;\n"
    "    overflow-y: scroll;\n"
    "    margin: 32px;\n"
    "}\n"
    ".network li {\n"
    "    margin-left: 5px;\n"
    "}\n"
    ".avatar img {\n"
    "    width: 48px;\n"
    "    height: 48px;\n"
    "    margin-right: 12px;\n"
    "    border-radius: 50%;\n"
    "    background-color: #cecece;\n"
    "    border: 2px solid #2e3136;\n"
    "}\n"
    ".user #name {\n"
    "    font-family: Quicksand, monospace;\n"
    "    color: #7289da;\n"
    "}\n"
    ".user #location {\n"
    "    font-family: Quicksand, monospace;\n"
    "    color: white;\n"
    "}\n"
    ".relations {\n"
    "    display: flex;\n"
    "}\n"
    ".relations h2 {\n"
    "    text-align: center;\n"
    "    font-size: 20px;\n"
    "}\n"
    "@media screen and (max-width: 730px) {\n"
    "    .relations {\n"
    "        display: inline-flex;\n"
    "        flex-direction: column;\n"
    "        overflow: hidden;\n"
    "        overflow-y: scroll;\n"
    "        padding-right: 32px;\n"
    "    }\n"
    "}\n"
    ".relations #mutuals p {\n"
    "    width: 128px;\n"
    "    text-align: center;\n"
    "}\n"
    ".relations ul {\n"
    "    overflow-y: scroll;\n"
    "    min-width: 100px;\n"
    "    height: calc(100vh - 370px);\n"
    "    border: 1px solid #36393e;\n"
    "    border-radius: 10px;\n"
    "    margin: 20px;\n"
    "    padding-top: 20px;\n"
    "    list-style: none;\n"
    "}\n"
    ".relations a, .network a {\n"
    "    display: block;\n"
    "    width: 128px;\n"
    "    overflow: hidden;\n"
    "    text-overflow: ellipsis;\n"
    "    white-space: nowrap;\n"
    "}\n"
    ".relations ul li {\n"
    "    position: relative;\n"
    "    cursor: pointer;\n"
    "}\n"
    ".relations ul li:before {\n"
    "    position: absolute;\n"
    "    top: 50%;\n"
    "    left: -20px;\n"
    "    width: 12px;\n"
    "    height: 12px;\n"
    "    content: '';\n"
    "    transition: all 0.3s;\n"
    "    background-image: url(\"data:image/svg+xml,%3C!--%3Fxml%20version%3D%221.0%22%20standalone%3D%22no%22%3F--%3E%0A%3Csvg%20id%3D%22sw-js-blob-svg%22%20viewBox%3D%220%200%20100%20100%22%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20version%3D%221.1%22%3E%0A%20%20%20%20%3Cdefs%3E%0A%20%20%20%20%20%20%20%20%3ClinearGradient%20id%3D%22sw-gradient%22%20x1%3D%220%22%20x2%3D%221%22%20y1%3D%221%22%20y2%3D%220%22%3E%0A%20%20%20%20%20%20%20%20%20%20%20%20%3Cstop%20id%3D%22stop1%22%20stop-color%3D%22rgba(114%2C%20137%2C%20218%2C%201)%22%20offset%3D%220%25%22%3E%3C%2Fstop%3E%0A%20%20%20%20%20%20%20%20%20%20%20%20%3Cstop%20id%3D%22stop2%22%20stop-color%3D%22rgba(184.527%2C%20198.869%2C%20249.379%2C%201)%22%20offset%3D%22100%25%22%3E%3C%2Fstop%3E%0A%20%20%20%20%20%20%20%20%3C%2FlinearGradient%3E%0A%20%20%20%20%3C%2Fdefs%3E%0A%20%20%20%20%3Cpath%20fill%3D%22url(%23sw-gradient)%22%20d%3D%22M20.8%2C12.6C13.6%2C24.4%2C-14.7%2C24.6%2C-21.7%2C12.9C-28.7%2C1.2%2C-14.3%2C-22.5%2C-0.2%2C-22.6C14%2C-22.7%2C28%2C0.8%2C20.8%2C12.6Z%22%20width%3D%22100%25%22%20height%3D%22100%25%22%20transform%3D%22translate(50%2050)%22%20stroke-width%3D%220%22%20style%3D%22transition%3A%20all%200.3s%20ease%200s%3B%22%20stroke%3D%22url(%23sw-gradient)%22%3E%3C%2Fpath%3E%0A%3C%2Fsvg%3E\");\n"
    "    background-position: center;\n"
    "    background-size: cover;\n"
    "    transform: translateY(-50%);\n"
    "}\n"
    ".relations ul li:hover:before {\n"
    "    left:-15px;\n"
    "}\n"
    ".value {\n"
    "    color: #7289da;\n"
    "}\n"
    "ul, li, h1, h2 {\n"
    "    font-family: Quicksand, monospace;\n"
    "    color: white;\n"
    "}\n"
    "a, p {\n"
    "    font-family: Quicksand, monospace;\n"
    "    color: #cecece;\n"
    "    text-decoration: none;\n"
    "}\n"
    "a:hover {\n"
    "    color: #7289da;\n"
    "}";

    file.close();
}


