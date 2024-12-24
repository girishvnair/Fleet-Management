#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <sqlite3.h>
#include <string>
#include <vector>

class DatabaseManager {
public:
    // Constructor opens a connection to the database
    DatabaseManager(const std::string& dbPath);

    // Destructor closes the connection
    ~DatabaseManager();

    // Executes a non-select SQL query
    void executeQuery(const std::string& query);

    // Executes a SELECT query and returns results
    std::vector<std::vector<std::string>> executeSelect(const std::string& query);

private:
    sqlite3* db = nullptr;
};

#endif // DATABASE_MANAGER_H
