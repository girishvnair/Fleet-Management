#include <iostream>
#include <string>
#include "utils/DatabaseManager.h"
#include "core/UserManager.h"
#include "core/VehicleManager.h"
#include "core/TripManager.h"
#include "core/FuelLogManager.h"
#include "core/MaintenanceLogManager.h"
#include "core/ComplianceManager.h"

void displayMainMenu() {
    std::cout << "\n--- Fleet Management System ---\n";
    std::cout << "1. Manage Users\n";
    std::cout << "2. Manage Vehicles\n";
    std::cout << "3. Manage Trips\n";
    std::cout << "4. Log Fuel Usage\n";
    std::cout << "5. Log Maintenance\n";
    std::cout << "6. Manage Compliance Records\n"; // New option for Compliance Records
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void handleComplianceManagement(ComplianceManager& complianceManager) {
    int choice;
    std::cout << "\n--- Compliance Records Management ---\n";
    std::cout << "1. Add Compliance Record\n";
    std::cout << "2. View Compliance Records by Vehicle\n";
    std::cout << "3. View All Compliance Records\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1: {
            ComplianceRecord record;
            std::cout << "Enter Vehicle ID: ";
            std::cin >> record.vehicleId;
            std::cout << "Enter Type (e.g., Inspection, Certification): ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, record.type);
            std::cout << "Enter Date (YYYY-MM-DD): ";
            std::cin >> record.date;
            std::cin.ignore(); // Clear input buffer
            std::cout << "Enter Description: ";
            std::getline(std::cin, record.description);
            if (complianceManager.addComplianceRecord(record)) {
                std::cout << "Compliance record added successfully.\n";
            } else {
                std::cout << "Failed to add compliance record.\n";
            }
            break;
        }
        case 2: {
            int vehicleId;
            std::cout << "Enter Vehicle ID: ";
            std::cin >> vehicleId;
            auto records = complianceManager.getComplianceRecordsByVehicle(vehicleId);
            if (records.empty()) {
                std::cout << "No compliance records found for this vehicle.\n";
            } else {
                for (const auto& record : records) {
                    std::cout << "Compliance Record ID: " << record.id
                              << ", Vehicle ID: " << record.vehicleId
                              << ", Type: " << record.type
                              << ", Date: " << record.date
                              << ", Description: " << record.description << "\n";
                }
            }
            break;
        }
        case 3: {
            auto records = complianceManager.getAllComplianceRecords();
            if (records.empty()) {
                std::cout << "No compliance records found.\n";
            } else {
                for (const auto& record : records) {
                    std::cout << "Compliance Record ID: " << record.id
                              << ", Vehicle ID: " << record.vehicleId
                              << ", Type: " << record.type
                              << ", Date: " << record.date
                              << ", Description: " << record.description << "\n";
                }
            }
            break;
        }
        case 0:
            return;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}

int main() {
    DatabaseManager dbManager("fleet_management.db");
    UserManager userManager(dbManager);
    VehicleManager vehicleManager(dbManager);
    TripManager tripManager(dbManager);
    FuelLogManager fuelLogManager(dbManager);
    MaintenanceLogManager maintenanceLogManager(dbManager);
    ComplianceManager complianceManager(dbManager);

    int choice;
    do {
        displayMainMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Existing user management
                break;
            case 2:
                // Existing vehicle management
                break;
            case 3:
                // Existing trip management
                break;
            case 4:
                // Existing fuel log management
                break;
            case 5:
                // Existing maintenance log management
                break;
            case 6:
                handleComplianceManagement(complianceManager); // New Compliance Records Management
                break;
            case 0:
                std::cout << "Exiting Fleet Management System. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
