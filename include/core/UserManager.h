#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <unordered_map>

class UserManager {
public:
    // Adds a new user to the system
    bool addUser(const std::string& username, const std::string& password);

    // Authenticates a user
    bool authenticate(const std::string& username, const std::string& password) const;

    // Removes a user from the system
    bool removeUser(const std::string& username);

private:
    // A map to store usernames and passwords
    std::unordered_map<std::string, std::string> users;
};

#endif // USER_MANAGER_H
