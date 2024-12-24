#include "core/ComplianceManager.h"
#include "utils/DatabaseManager.h"
#include <cassert>
#include <iostream>

void testAddComplianceRecord() {
    DatabaseManager dbManager("test_fleet_management.db");
    ComplianceManager complianceManager(dbManager);

    ComplianceRecord record1 = {0, 1, "Inspection", "2024-12-25", "Annual inspection completed"};
    ComplianceRecord record2 = {0, 1, "Certification", "2024-12-26", "Emission certification obtained"};

    assert(complianceManager.addComplianceRecord(record1) == true); // Add new compliance record
    assert(complianceManager.addComplianceRecord(record2) == true); // Add another compliance record

    std::cout << "testAddComplianceRecord passed!" << std::endl;
}

void testGetComplianceRecordsByVehicle() {
    DatabaseManager dbManager("test_fleet_management.db");
    ComplianceManager complianceManager(dbManager);

    auto records = complianceManager.getComplianceRecordsByVehicle(1);
    assert(!records.empty()); // Ensure records exist for the vehicle

    for (const auto& record : records) {
        std::cout << "ComplianceRecord ID: " << record.id
                  << ", Vehicle ID: " << record.vehicleId
                  << ", Type: " << record.type
                  << ", Date: " << record.date
                  << ", Description: " << record.description << std::endl;
    }

    std::cout << "testGetComplianceRecordsByVehicle passed!" << std::endl;
}

void testGetAllComplianceRecords() {
    DatabaseManager dbManager("test_fleet_management.db");
    ComplianceManager complianceManager(dbManager);

    auto records = complianceManager.getAllComplianceRecords();
    assert(!records.empty()); // Ensure records are retrieved from the database

    for (const auto& record : records) {
        std::cout << "ComplianceRecord ID: " << record.id
                  << ", Vehicle ID: " << record.vehicleId
                  << ", Type: " << record.type
                  << ", Date: " << record.date
                  << ", Description: " << record.description << std::endl;
    }

    std::cout << "testGetAllComplianceRecords passed!" << std::endl;
}

int main() {
    try {
        testAddComplianceRecord();
        testGetComplianceRecordsByVehicle();
        testGetAllComplianceRecords();
        std::cout << "All ComplianceManager tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
