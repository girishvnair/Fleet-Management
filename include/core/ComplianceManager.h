#ifndef COMPLIANCE_MANAGER_H
#define COMPLIANCE_MANAGER_H

#include <string>
#include <vector>
#include "utils/DatabaseManager.h"

struct ComplianceRecord {
    int id;
    int vehicleId;
    std::string type;         // Type of compliance, e.g., "Inspection", "Certification"
    std::string date;         // Date of the compliance activity
    std::string description;  // Details about the compliance activity
};

class ComplianceManager {
public:
    // Constructor
    explicit ComplianceManager(DatabaseManager& dbManager);

    // Adds a new compliance record
    bool addComplianceRecord(const ComplianceRecord& record);

    // Retrieves all compliance records for a specific vehicle
    std::vector<ComplianceRecord> getComplianceRecordsByVehicle(int vehicleId) const;

    // Retrieves all compliance records
    std::vector<ComplianceRecord> getAllComplianceRecords() const;

private:
    DatabaseManager& dbManager;
};

#endif // COMPLIANCE_MANAGER_H
