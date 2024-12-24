#ifndef MAINTENANCE_LOG_MANAGER_H
#define MAINTENANCE_LOG_MANAGER_H

#include <string>
#include <vector>
#include "utils/DatabaseManager.h"

struct MaintenanceLog {
    int id;
    int vehicleId;
    std::string date;
    std::string description;
};

class MaintenanceLogManager {
public:
    // Constructor
    explicit MaintenanceLogManager(DatabaseManager& dbManager);

    // Adds a new maintenance log
    bool addMaintenanceLog(const MaintenanceLog& log);

    // Retrieves all maintenance logs for a specific vehicle
    std::vector<MaintenanceLog> getMaintenanceLogsByVehicle(int vehicleId) const;

    // Retrieves all maintenance logs
    std::vector<MaintenanceLog> getAllMaintenanceLogs() const;

private:
    DatabaseManager& dbManager;
};

#endif // MAINTENANCE_LOG_MANAGER_H
