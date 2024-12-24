#include "core/DriverManager.h"
#include "utils/DatabaseManager.h"
#include <cassert>
#include <iostream>

void testAddDriver() {
    DatabaseManager dbManager("test_fleet_management.db");
    DriverManager driverManager(dbManager);

    Driver driver1 = {0, "John Doe", "DL12345", "555-1234"};
    Driver driver2 = {0, "Jane Smith", "DL67890", "555-5678"};

    assert(driverManager.addDriver(driver1) == true); // Add new driver
    assert(driverManager.addDriver(driver2) == true); // Add another driver
    assert(driverManager.addDriver(driver1) == false); // Duplicate license number

    std::cout << "testAddDriver passed!" << std::endl;
}

void testUpdateDriver() {
    DatabaseManager dbManager("test_fleet_management.db");
    DriverManager driverManager(dbManager);

    int driverId = 1; // Assuming the first driver ID is 1
    assert(driverManager.updateDriver(driverId, "John Updated", "555-0000") == true); // Update driver
    assert(driverManager.updateDriver(9999, "Nonexistent", "555-9999") == false); // Nonexistent driver

    std::cout << "testUpdateDriver passed!" << std::endl;
}

void testGetAllDrivers() {
    DatabaseManager dbManager("test_fleet_management.db");
    DriverManager driverManager(dbManager);

    auto drivers = driverManager.getAllDrivers();
    assert(!drivers.empty()); // Ensure at least one driver exists

    for (const auto& driver : drivers) {
        std::cout << "Driver ID: " << driver.id
                  << ", Name: " << driver.name
                  << ", License Number: " << driver.licenseNumber
                  << ", Phone Number: " << driver.phoneNumber << std::endl;
    }

    std::cout << "testGetAllDrivers passed!" << std::endl;
}

int main() {
    try {
        testAddDriver();
        testUpdateDriver();
        testGetAllDrivers();
        std::cout << "All DriverManager tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
