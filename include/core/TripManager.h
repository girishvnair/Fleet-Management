#ifndef TRIP_MANAGER_H
#define TRIP_MANAGER_H

#include <string>
#include <vector>
#include "utils/DatabaseManager.h"

struct Trip {
    int id;
    int vehicleId;
    int userId;
    std::string startTime;
    std::string endTime;
    std::string startLocation;
    std::string endLocation;
};

class TripManager {
public:
    // Constructor
    explicit TripManager(DatabaseManager& dbManager);

    // Starts a new trip
    bool startTrip(const Trip& trip);

    // Ends an existing trip
    bool endTrip(int tripId, const std::string& endTime, const std::string& endLocation);

    // Retrieves all trips
    std::vector<Trip> getAllTrips() const;

private:
    DatabaseManager& dbManager;
};

#endif // TRIP_MANAGER_H
