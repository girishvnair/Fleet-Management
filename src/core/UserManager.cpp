#include "core/UserManager.h"

bool UserManager::addUser(const std::string& username, const std::string& password) {
    // Check if the user already exists
    if (users.find(username) != users.end()) {
        return false; // User already exists
    }
    // Add the new user
    users[username] = password;
    return true;
}

bool UserManager::authenticate(const std::string& username, const std::string& password) const {
    // Check if the user exists and the password matches
    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        return true; // Authentication successful
    }
    return false; // Authentication failed
}

bool UserManager::removeUser(const std::string& username) {
    // Remove the user if they exist
    return users.erase(username) > 0;
}
