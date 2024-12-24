#include "core/VehicleManager.h"
#include <stdexcept>

VehicleManager::VehicleManager(DatabaseManager& dbManager) : dbManager(dbManager) {}

bool VehicleManager::addVehicle(const Vehicle& vehicle) {
    try {
        std::string query = "INSERT INTO Vehicles (license_plate, make, model, year, status) VALUES ('" +
                            vehicle.licensePlate + "', '" + vehicle.make + "', '" + vehicle.model + "', " +
                            std::to_string(vehicle.year) + ", '" + vehicle.status + "');";
        dbManager.executeQuery(query);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool VehicleManager::updateVehicleStatus(const std::string& licensePlate, const std::string& status) {
    try {
        std::string query = "UPDATE Vehicles SET status = '" + status + "' WHERE license_plate = '" + licensePlate + "';";
        dbManager.executeQuery(query);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::vector<Vehicle> VehicleManager::getAllVehicles() const {
    std::vector<Vehicle> vehicles;
    std::string query = "SELECT id, license_plate, make, model, year, status FROM Vehicles;";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        Vehicle vehicle;
        vehicle.id = std::stoi(row[0]);
        vehicle.licensePlate = row[1];
        vehicle.make = row[2];
        vehicle.model = row[3];
        vehicle.year = std::stoi(row[4]);
        vehicle.status = row[5];
        vehicles.push_back(vehicle);
    }
    return vehicles;
}
