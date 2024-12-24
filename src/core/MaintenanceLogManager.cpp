#include "core/MaintenanceLogManager.h"
#include <stdexcept>

MaintenanceLogManager::MaintenanceLogManager(DatabaseManager& dbManager) : dbManager(dbManager) {}

bool MaintenanceLogManager::addMaintenanceLog(const MaintenanceLog& log) {
    try {
        std::string query = "INSERT INTO MaintenanceLogs (vehicle_id, date, description) VALUES (" +
                            std::to_string(log.vehicleId) + ", '" + log.date + "', '" + log.description + "');";
        dbManager.executeQuery(query);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::vector<MaintenanceLog> MaintenanceLogManager::getMaintenanceLogsByVehicle(int vehicleId) const {
    std::vector<MaintenanceLog> logs;
    std::string query = "SELECT id, vehicle_id, date, description FROM MaintenanceLogs WHERE vehicle_id = " +
                        std::to_string(vehicleId) + ";";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        MaintenanceLog log;
        log.id = std::stoi(row[0]);
        log.vehicleId = std::stoi(row[1]);
        log.date = row[2];
        log.description = row[3];
        logs.push_back(log);
    }
    return logs;
}

std::vector<MaintenanceLog> MaintenanceLogManager::getAllMaintenanceLogs() const {
    std::vector<MaintenanceLog> logs;
    std::string query = "SELECT id, vehicle_id, date, description FROM MaintenanceLogs;";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        MaintenanceLog log;
        log.id = std::stoi(row[0]);
        log.vehicleId = std::stoi(row[1]);
        log.date = row[2];
        log.description = row[3];
        logs.push_back(log);
    }
    return logs;
}
