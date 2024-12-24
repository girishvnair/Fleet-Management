const BASE_URL = 'http://localhost:5000/api'; // Replace with your backend URL

// VEHICLES API FUNCTIONS

// Fetch all vehicles
export const fetchVehicles = async () => {
  const response = await fetch(`${BASE_URL}/vehicles`);
  return response.json();
};

// Add a new vehicle
export const addVehicle = async (vehicle) => {
  const response = await fetch(`${BASE_URL}/vehicles`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(vehicle),
  });
  return response.json();
};

// Delete a vehicle
export const deleteVehicle = async (id) => {
  const response = await fetch(`${BASE_URL}/vehicles/${id}`, { method: 'DELETE' });
  return response.json();
};

// TRIPS API FUNCTIONS

// Fetch all trips
export const fetchTrips = async () => {
  const response = await fetch(`${BASE_URL}/trips`);
  return response.json();
};

// Add a new trip
export const addTrip = async (trip) => {
  const response = await fetch(`${BASE_URL}/trips`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(trip),
  });
  return response.json();
};
// Fetch all fuel logs
export const fetchFuelLogs = async () => {
  const response = await fetch(`${BASE_URL}/fuel-logs`);
  return response.json();
};

// Add a new fuel log
export const addFuelLog = async (fuelLog) => {
  const response = await fetch(`${BASE_URL}/fuel-logs`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(fuelLog),
  });
  return response.json();
};

// Delete a fuel log
export const deleteFuelLog = async (id) => {
  const response = await fetch(`${BASE_URL}/fuel-logs/${id}`, { method: 'DELETE' });
  return response.json();
};
// Fetch all maintenance logs
export const fetchMaintenanceLogs = async () => {
  const response = await fetch(`${BASE_URL}/maintenance-logs`);
  return response.json();
};

// Add a new maintenance log
export const addMaintenanceLog = async (log) => {
  const response = await fetch(`${BASE_URL}/maintenance-logs`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(log),
  });
  return response.json();
};

// Delete a maintenance log
export const deleteMaintenanceLog = async (id) => {
  const response = await fetch(`${BASE_URL}/maintenance-logs/${id}`, { method: 'DELETE' });
  return response.json();
};
// Fetch all compliance records
export const fetchComplianceRecords = async () => {
  const response = await fetch(`${BASE_URL}/compliance-records`);
  return response.json();
};

// Add a new compliance record
export const addComplianceRecord = async (record) => {
  const response = await fetch(`${BASE_URL}/compliance-records`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(record),
  });
  return response.json();
};

// Delete a compliance record
export const deleteComplianceRecord = async (id) => {
  const response = await fetch(`${BASE_URL}/compliance-records/${id}`, { method: 'DELETE' });
  return response.json();
};
