//
// Created by Justin on 9/16/2022.
//

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#define COMPILED_IN_LINUX
#include <sys/types.h>
#include <unistd.h>
#elif defined(__APPLE__) && defined(__MACH__)
#define COMPILED_IN_MACOS
#include <sys/types.h>
#include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
#define COMPILED_IN_WINDOWS
#include <windows.h>

#endif

#ifndef PROJECT1_315_SOCIALNETWORK_HPP
#define PROJECT1_315_SOCIALNETWORK_HPP

#include "User.hpp"
#include "JSONParser.hpp"
#include <map>
#include <sys/stat.h>

const char DIRECTORY_NAME[] = "SocialNetwork"; // set directory name for html files

class SocialNetwork {
public:
    // DEFAULT CONSTRUCTOR
    SocialNetwork();

    // PARAMETERIZED CONSTRUCTOR
    explicit SocialNetwork(const std::string &inputFile);

    // GET PROFILE MAP
    const std::map<int, User> &getProfileMap() const { return _userMap; }

    // SET PROFILE MAP
    void setProfileMap(const std::map<int, User> &users) { _userMap = users; }

    // OUTPUT HTML FILES
    void generateHTML(bool withCSS = false);

    // OPEN INDEX.HTML
    static void open();

    // RETURN NUMBER OF USERS
    size_t size() { return _userMap.size(); }

    // IS THE SOCIAL NETWORK EMPTY?
    bool empty() { return _userMap.empty(); }

private:
    // CREATE SOCIAL NETWORK DIRECTORY
    static bool createDirectory();

    // OUTPUT CSS
    static void generateCSS();

    // MAP OF PROFILES
    std::map<int, User> _userMap;
};

#endif //PROJECT1_315_SOCIALNETWORK_HPP
