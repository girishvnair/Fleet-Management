#ifndef VEHICLE_MANAGER_H
#define VEHICLE_MANAGER_H

#include <string>
#include <vector>
#include "utils/DatabaseManager.h"

struct Vehicle {
    int id;
    std::string licensePlate;
    std::string make;
    std::string model;
    int year;
    std::string status;
};

class VehicleManager {
public:
    // Constructor
    explicit VehicleManager(DatabaseManager& dbManager);

    // Adds a new vehicle
    bool addVehicle(const Vehicle& vehicle);

    // Updates the status of a vehicle
    bool updateVehicleStatus(const std::string& licensePlate, const std::string& status);

    // Retrieves all vehicles
    std::vector<Vehicle> getAllVehicles() const;

private:
    DatabaseManager& dbManager;
};

#endif // VEHICLE_MANAGER_H
