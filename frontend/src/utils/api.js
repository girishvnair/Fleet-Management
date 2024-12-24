const BASE_URL = 'http://localhost:5000/api'; // Adjust backend URL as needed

// Fetch all vehicles
export const fetchVehicles = async () => {
  try {
    const response = await fetch(`${BASE_URL}/vehicles`);
    return await response.json();
  } catch (error) {
    console.error('Error fetching vehicles:', error);
    return [];
  }
};

// Add a new vehicle
export const addVehicle = async (vehicle) => {
  try {
    const response = await fetch(`${BASE_URL}/vehicles`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(vehicle),
    });
    return await response.json();
  } catch (error) {
    console.error('Error adding vehicle:', error);
    return null;
  }
};
