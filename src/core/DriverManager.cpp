#include "core/DriverManager.h"
#include <stdexcept>

DriverManager::DriverManager(DatabaseManager& dbManager) : dbManager(dbManager) {}

bool DriverManager::addDriver(const Driver& driver) {
    try {
        std::string query = "INSERT INTO Users (username, password) VALUES ('" +
                            driver.licenseNumber + "', 'driver_password');";
        dbManager.executeQuery(query);

        // Optionally, store additional driver details in another table if needed
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool DriverManager::updateDriver(int driverId, const std::string& name, const std::string& phoneNumber) {
    try {
        std::string query = "UPDATE Users SET username = '" + name + "', password = '" + phoneNumber +
                            "' WHERE id = " + std::to_string(driverId) + ";";
        dbManager.executeQuery(query);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::vector<Driver> DriverManager::getAllDrivers() const {
    std::vector<Driver> drivers;
    std::string query = "SELECT id, username, password FROM Users;";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        Driver driver;
        driver.id = std::stoi(row[0]);
        driver.name = row[1];
        driver.licenseNumber = row[1];
        driver.phoneNumber = row[2];
        drivers.push_back(driver);
    }
    return drivers;
}
