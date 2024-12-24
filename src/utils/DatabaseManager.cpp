#include "utils/DatabaseManager.h"
#include <stdexcept>
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Failed to open database: " + dbPath);
    }
}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}

void DatabaseManager::executeQuery(const std::string& query) {
    char* errorMessage = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::string error = errorMessage;
        sqlite3_free(errorMessage);
        throw std::runtime_error("SQL error: " + error);
    }
}

std::vector<std::vector<std::string>> DatabaseManager::executeSelect(const std::string& query) {
    sqlite3_stmt* stmt;
    std::vector<std::vector<std::string>> results;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare query: " + query);
    }

    int columns = sqlite3_column_count(stmt);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int i = 0; i < columns; i++) {
            const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row.push_back(text ? text : "");
        }
        results.push_back(row);
    }

    sqlite3_finalize(stmt);
    return results;
}
