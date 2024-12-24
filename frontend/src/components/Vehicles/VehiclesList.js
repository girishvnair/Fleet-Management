import React, { useEffect, useState } from 'react';
import { fetchVehicles, addVehicle } from '../../utils/api';

const VehiclesList = () => {
  const [vehicles, setVehicles] = useState([]);
  const [newVehicle, setNewVehicle] = useState({
    licensePlate: '',
    make: '',
    model: '',
    year: '',
    status: '',
  });

  useEffect(() => {
    const getVehicles = async () => {
      const data = await fetchVehicles();
      setVehicles(data);
    };
    getVehicles();
  }, []);

  const handleChange = (e) => {
    setNewVehicle({ ...newVehicle, [e.target.name]: e.target.value });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const addedVehicle = await addVehicle(newVehicle);
    if (addedVehicle) {
      setVehicles([...vehicles, addedVehicle]);
      setNewVehicle({ licensePlate: '', make: '', model: '', year: '', status: '' });
    }
  };

  return (
    <div>
      <h2>Vehicle Management</h2>
      <form onSubmit={handleSubmit}>
        <input
          type="text"
          name="licensePlate"
          placeholder="License Plate"
          value={newVehicle.licensePlate}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="make"
          placeholder="Make"
          value={newVehicle.make}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="model"
          placeholder="Model"
          value={newVehicle.model}
          onChange={handleChange}
          required
        />
        <input
          type="number"
          name="year"
          placeholder="Year"
          value={newVehicle.year}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="status"
          placeholder="Status"
          value={newVehicle.status}
          onChange={handleChange}
          required
        />
        <button type="submit">Add Vehicle</button>
      </form>
      <table>
        <thead>
          <tr>
            <th>License Plate</th>
            <th>Make</th>
            <th>Model</th>
            <th>Year</th>
            <th>Status</th>
          </tr>
        </thead>
        <tbody>
          {vehicles.map((vehicle) => (
            <tr key={vehicle.id}>
              <td>{vehicle.licensePlate}</td>
              <td>{vehicle.make}</td>
              <td>{vehicle.model}</td>
              <td>{vehicle.year}</td>
              <td>{vehicle.status}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default VehiclesList;
