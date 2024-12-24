#include "core/ComplianceManager.h"
#include <stdexcept>

ComplianceManager::ComplianceManager(DatabaseManager& dbManager) : dbManager(dbManager) {}

bool ComplianceManager::addComplianceRecord(const ComplianceRecord& record) {
    try {
        std::string query = "INSERT INTO ComplianceRecords (vehicle_id, type, date, description) VALUES (" +
                            std::to_string(record.vehicleId) + ", '" + record.type + "', '" + record.date + "', '" +
                            record.description + "');";
        dbManager.executeQuery(query);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::vector<ComplianceRecord> ComplianceManager::getComplianceRecordsByVehicle(int vehicleId) const {
    std::vector<ComplianceRecord> records;
    std::string query = "SELECT id, vehicle_id, type, date, description FROM ComplianceRecords WHERE vehicle_id = " +
                        std::to_string(vehicleId) + ";";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        ComplianceRecord record;
        record.id = std::stoi(row[0]);
        record.vehicleId = std::stoi(row[1]);
        record.type = row[2];
        record.date = row[3];
        record.description = row[4];
        records.push_back(record);
    }
    return records;
}

std::vector<ComplianceRecord> ComplianceManager::getAllComplianceRecords() const {
    std::vector<ComplianceRecord> records;
    std::string query = "SELECT id, vehicle_id, type, date, description FROM ComplianceRecords;";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        ComplianceRecord record;
        record.id = std::stoi(row[0]);
        record.vehicleId = std::stoi(row[1]);
        record.type = row[2];
        record.date = row[3];
        record.description = row[4];
        records.push_back(record);
    }
    return records;
}
