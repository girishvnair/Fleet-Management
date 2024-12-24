#include "core/TripManager.h"
#include <stdexcept>

TripManager::TripManager(DatabaseManager& dbManager) : dbManager(dbManager) {}

bool TripManager::startTrip(const Trip& trip) {
    try {
        std::string query = "INSERT INTO Trips (vehicle_id, user_id, start_time, start_location) VALUES (" +
                            std::to_string(trip.vehicleId) + ", " + std::to_string(trip.userId) + ", '" +
                            trip.startTime + "', '" + trip.startLocation + "');";
        dbManager.executeQuery(query);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool TripManager::endTrip(int tripId, const std::string& endTime, const std::string& endLocation) {
    try {
        std::string query = "UPDATE Trips SET end_time = '" + endTime + "', end_location = '" + endLocation +
                            "' WHERE id = " + std::to_string(tripId) + ";";
        dbManager.executeQuery(query);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::vector<Trip> TripManager::getAllTrips() const {
    std::vector<Trip> trips;
    std::string query = "SELECT id, vehicle_id, user_id, start_time, end_time, start_location, end_location FROM Trips;";
    auto results = dbManager.executeSelect(query);

    for (const auto& row : results) {
        Trip trip;
        trip.id = std::stoi(row[0]);
        trip.vehicleId = std::stoi(row[1]);
        trip.userId = std::stoi(row[2]);
        trip.startTime = row[3];
        trip.endTime = row[4];
        trip.startLocation = row[5];
        trip.endLocation = row[6];
        trips.push_back(trip);
    }
    return trips;
}
