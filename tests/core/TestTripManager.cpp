#include "core/TripManager.h"
#include "utils/DatabaseManager.h"
#include <cassert>
#include <iostream>

void testStartTrip() {
    DatabaseManager dbManager("test_fleet_management.db");
    TripManager tripManager(dbManager);

    Trip trip = {0, 1, 1, "2024-12-25 10:00:00", "", "Stockholm", ""};
    assert(tripManager.startTrip(trip) == true); // Start a new trip
    std::cout << "testStartTrip passed!" << std::endl;
}

void testEndTrip() {
    DatabaseManager dbManager("test_fleet_management.db");
    TripManager tripManager(dbManager);

    int tripId = 1; // Assuming the first trip ID is 1
    assert(tripManager.endTrip(tripId, "2024-12-25 15:00:00", "Gothenburg") == true); // End the trip
    assert(tripManager.endTrip(9999, "2024-12-25 15:00:00", "Gothenburg") == false); // Nonexistent trip
    std::cout << "testEndTrip passed!" << std::endl;
}

void testGetAllTrips() {
    DatabaseManager dbManager("test_fleet_management.db");
    TripManager tripManager(dbManager);

    auto trips = tripManager.getAllTrips();
    assert(!trips.empty()); // Ensure at least one trip exists

    for (const auto& trip : trips) {
        std::cout << "Trip ID: " << trip.id
                  << ", Vehicle ID: " << trip.vehicleId
                  << ", User ID: " << trip.userId
                  << ", Start Time: " << trip.startTime
                  << ", End Time: " << trip.endTime
                  << ", Start Location: " << trip.startLocation
                  << ", End Location: " << trip.endLocation << std::endl;
    }

    std::cout << "testGetAllTrips passed!" << std::endl;
}

int main() {
    try {
        testStartTrip();
        testEndTrip();
        testGetAllTrips();
        std::cout << "All TripManager tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
