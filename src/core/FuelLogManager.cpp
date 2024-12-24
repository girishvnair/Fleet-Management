#include "core/FuelLogManager.h"
#include <stdexcept>

FuelLogManager::FuelLogManager(DatabaseManager& dbManager) : dbManager(dbManager) {}

bool FuelLogManager::addFuelLog(const FuelLog& fuelLog) {
    try {
        std::string query = "INSERT INTO FuelLogs (vehicle_id, date, fuel_amount, cost) VALUES (" +
                            std::to_string(fuelLog.vehicleId) + ", '" + fuelLog.date + "', " +
                            std::to_string(fuelLog.fuelAmount) + ", " + std::to_string(fuelLog.cost) + ");";
        dbManager.executeQuery(query);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::vector<FuelLog> FuelLogManager::getFuelLogsByVehicle(int vehicleId) const {
    std::vector<FuelLog> fuelLogs;
    std::string query = "SELECT id, vehicle_id, date, fuel_amount, cost FROM FuelLogs WHERE vehicle_id = " +
                        std::to_string(vehicleId) + ";";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        FuelLog fuelLog;
        fuelLog.id = std::stoi(row[0]);
        fuelLog.vehicleId = std::stoi(row[1]);
        fuelLog.date = row[2];
        fuelLog.fuelAmount = std::stod(row[3]);
        fuelLog.cost = std::stod(row[4]);
        fuelLogs.push_back(fuelLog);
    }
    return fuelLogs;
}

std::vector<FuelLog> FuelLogManager::getAllFuelLogs() const {
    std::vector<FuelLog> fuelLogs;
    std::string query = "SELECT id, vehicle_id, date, fuel_amount, cost FROM FuelLogs;";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        FuelLog fuelLog;
        fuelLog.id = std::stoi(row[0]);
        fuelLog.vehicleId = std::stoi(row[1]);
        fuelLog.date = row[2];
        fuelLog.fuelAmount = std::stod(row[3]);
        fuelLog.cost = std::stod(row[4]);
        fuelLogs.push_back(fuelLog);
    }
    return fuelLogs;
}
