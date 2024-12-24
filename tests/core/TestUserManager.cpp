#include "core/UserManager.h"
#include <cassert>
#include <iostream>

void testAddUser() {
    UserManager manager;
    assert(manager.addUser("user1", "password1") == true); // New user added
    assert(manager.addUser("user1", "password1") == false); // Duplicate user
    std::cout << "testAddUser passed!" << std::endl;
}

void testAuthenticate() {
    UserManager manager;
    manager.addUser("user1", "password1");
    assert(manager.authenticate("user1", "password1") == true); // Correct credentials
    assert(manager.authenticate("user1", "wrongpassword") == false); // Wrong password
    assert(manager.authenticate("user2", "password1") == false); // Nonexistent user
    std::cout << "testAuthenticate passed!" << std::endl;
}

void testRemoveUser() {
    UserManager manager;
    manager.addUser("user1", "password1");
    assert(manager.removeUser("user1") == true); // User removed
    assert(manager.removeUser("user1") == false); // User no longer exists
    std::cout << "testRemoveUser passed!" << std::endl;
}

int main() {
    testAddUser();
    testAuthenticate();
    testRemoveUser();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
