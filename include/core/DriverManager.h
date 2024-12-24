#ifndef DRIVER_MANAGER_H
#define DRIVER_MANAGER_H

#include <string>
#include <vector>
#include "utils/DatabaseManager.h"

struct Driver {
    int id;
    std::string name;
    std::string licenseNumber;
    std::string phoneNumber;
};

class DriverManager {
public:
    // Constructor
    explicit DriverManager(DatabaseManager& dbManager);

    // Adds a new driver
    bool addDriver(const Driver& driver);

    // Updates driver information
    bool updateDriver(int driverId, const std::string& name, const std::string& phoneNumber);

    // Retrieves all drivers
    std::vector<Driver> getAllDrivers() const;

private:
    DatabaseManager& dbManager;
};

#endif // DRIVER_MANAGER_H
