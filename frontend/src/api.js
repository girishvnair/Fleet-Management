export const fetchVehicles = async () => {
  try {
    const response = await fetch('http://localhost:5000/api/vehicles'); // Adjust URL as needed
    return await response.json();
  } catch (error) {
    console.error('Error fetching vehicles:', error);
    return [];
  }
};
