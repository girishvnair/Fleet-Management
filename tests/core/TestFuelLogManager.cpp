#include "core/FuelLogManager.h"
#include "utils/DatabaseManager.h"
#include <cassert>
#include <iostream>

void testAddFuelLog() {
    DatabaseManager dbManager("test_fleet_management.db");
    FuelLogManager fuelLogManager(dbManager);

    FuelLog log1 = {0, 1, "2024-12-25", 50.5, 75.0};
    FuelLog log2 = {0, 1, "2024-12-26", 30.0, 45.0};

    assert(fuelLogManager.addFuelLog(log1) == true); // Add a new log
    assert(fuelLogManager.addFuelLog(log2) == true); // Add another log

    std::cout << "testAddFuelLog passed!" << std::endl;
}

void testGetFuelLogsByVehicle() {
    DatabaseManager dbManager("test_fleet_management.db");
    FuelLogManager fuelLogManager(dbManager);

    auto logs = fuelLogManager.getFuelLogsByVehicle(1);
    assert(!logs.empty()); // Ensure at least one log exists for the vehicle

    for (const auto& log : logs) {
        std::cout << "FuelLog ID: " << log.id
                  << ", Vehicle ID: " << log.vehicleId
                  << ", Date: " << log.date
                  << ", Fuel Amount: " << log.fuelAmount
                  << ", Cost: " << log.cost << std::endl;
    }

    std::cout << "testGetFuelLogsByVehicle passed!" << std::endl;
}

void testGetAllFuelLogs() {
    DatabaseManager dbManager("test_fleet_management.db");
    FuelLogManager fuelLogManager(dbManager);

    auto logs = fuelLogManager.getAllFuelLogs();
    assert(!logs.empty()); // Ensure logs are retrieved from the database

    for (const auto& log : logs) {
        std::cout << "FuelLog ID: " << log.id
                  << ", Vehicle ID: " << log.vehicleId
                  << ", Date: " << log.date
                  << ", Fuel Amount: " << log.fuelAmount
                  << ", Cost: " << log.cost << std::endl;
    }

    std::cout << "testGetAllFuelLogs passed!" << std::endl;
}

int main() {
    try {
        testAddFuelLog();
        testGetFuelLogsByVehicle();
        testGetAllFuelLogs();
        std::cout << "All FuelLogManager tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
