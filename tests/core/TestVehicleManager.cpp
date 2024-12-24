#include "core/VehicleManager.h"
#include "utils/DatabaseManager.h"
#include <cassert>
#include <iostream>

void testAddVehicle() {
    DatabaseManager dbManager("test_fleet_management.db");
    VehicleManager vehicleManager(dbManager);

    Vehicle vehicle1 = {0, "ABC123", "Toyota", "Camry", 2020, "Available"};
    Vehicle vehicle2 = {0, "XYZ789", "Honda", "Civic", 2018, "In Maintenance"};

    assert(vehicleManager.addVehicle(vehicle1) == true); // Add a new vehicle
    assert(vehicleManager.addVehicle(vehicle2) == true); // Add another vehicle
    assert(vehicleManager.addVehicle(vehicle1) == false); // Duplicate license plate

    std::cout << "testAddVehicle passed!" << std::endl;
}

void testUpdateVehicleStatus() {
    DatabaseManager dbManager("test_fleet_management.db");
    VehicleManager vehicleManager(dbManager);

    assert(vehicleManager.updateVehicleStatus("ABC123", "In Use") == true); // Update status
    assert(vehicleManager.updateVehicleStatus("NONEXISTENT", "Available") == false); // Nonexistent vehicle

    std::cout << "testUpdateVehicleStatus passed!" << std::endl;
}

void testGetAllVehicles() {
    DatabaseManager dbManager("test_fleet_management.db");
    VehicleManager vehicleManager(dbManager);

    auto vehicles = vehicleManager.getAllVehicles();
    assert(!vehicles.empty()); // Ensure at least one vehicle exists

    for (const auto& vehicle : vehicles) {
        std::cout << "Vehicle ID: " << vehicle.id
                  << ", License Plate: " << vehicle.licensePlate
                  << ", Make: " << vehicle.make
                  << ", Model: " << vehicle.model
                  << ", Year: " << vehicle.year
                  << ", Status: " << vehicle.status << std::endl;
    }

    std::cout << "testGetAllVehicles passed!" << std::endl;
}

int main() {
    try {
        testAddVehicle();
        testUpdateVehicleStatus();
        testGetAllVehicles();
        std::cout << "All VehicleManager tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
