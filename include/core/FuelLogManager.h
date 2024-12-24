#ifndef FUEL_LOG_MANAGER_H
#define FUEL_LOG_MANAGER_H

#include <string>
#include <vector>
#include "utils/DatabaseManager.h"

struct FuelLog {
    int id;
    int vehicleId;
    std::string date;
    double fuelAmount;
    double cost;
};

class FuelLogManager {
public:
    // Constructor
    explicit FuelLogManager(DatabaseManager& dbManager);

    // Adds a new fuel log
    bool addFuelLog(const FuelLog& fuelLog);

    // Retrieves all fuel logs for a specific vehicle
    std::vector<FuelLog> getFuelLogsByVehicle(int vehicleId) const;

    // Retrieves all fuel logs
    std::vector<FuelLog> getAllFuelLogs() const;

private:
    DatabaseManager& dbManager;
};

#endif // FUEL_LOG_MANAGER_H
