#include "core/MaintenanceLogManager.h"
#include "utils/DatabaseManager.h"
#include <cassert>
#include <iostream>

void testAddMaintenanceLog() {
    DatabaseManager dbManager("test_fleet_management.db");
    MaintenanceLogManager logManager(dbManager);

    MaintenanceLog log1 = {0, 1, "2024-12-25", "Oil change"};
    MaintenanceLog log2 = {0, 1, "2024-12-26", "Brake pad replacement"};

    assert(logManager.addMaintenanceLog(log1) == true); // Add a new maintenance log
    assert(logManager.addMaintenanceLog(log2) == true); // Add another maintenance log

    std::cout << "testAddMaintenanceLog passed!" << std::endl;
}

void testGetMaintenanceLogsByVehicle() {
    DatabaseManager dbManager("test_fleet_management.db");
    MaintenanceLogManager logManager(dbManager);

    auto logs = logManager.getMaintenanceLogsByVehicle(1);
    assert(!logs.empty()); // Ensure logs exist for the vehicle

    for (const auto& log : logs) {
        std::cout << "MaintenanceLog ID: " << log.id
                  << ", Vehicle ID: " << log.vehicleId
                  << ", Date: " << log.date
                  << ", Description: " << log.description << std::endl;
    }

    std::cout << "testGetMaintenanceLogsByVehicle passed!" << std::endl;
}

void testGetAllMaintenanceLogs() {
    DatabaseManager dbManager("test_fleet_management.db");
    MaintenanceLogManager logManager(dbManager);

    auto logs = logManager.getAllMaintenanceLogs();
    assert(!logs.empty()); // Ensure logs are retrieved from the database

    for (const auto& log : logs) {
        std::cout << "MaintenanceLog ID: " << log.id
                  << ", Vehicle ID: " << log.vehicleId
                  << ", Date: " << log.date
                  << ", Description: " << log.description << std::endl;
    }

    std::cout << "testGetAllMaintenanceLogs passed!" << std::endl;
}

int main() {
    try {
        testAddMaintenanceLog();
        testGetMaintenanceLogsByVehicle();
        testGetAllMaintenanceLogs();
        std::cout << "All MaintenanceLogManager tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
