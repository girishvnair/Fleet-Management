import React, { useEffect, useState } from 'react';
import { fetchTrips, addTrip } from '../../utils/api';

const TripsList = () => {
  const [trips, setTrips] = useState([]);
  const [newTrip, setNewTrip] = useState({
    route: '',
    vehicle: '',
    driver: '',
    status: '',
  });

  useEffect(() => {
    const getTrips = async () => {
      const data = await fetchTrips();
      setTrips(data);
    };
    getTrips();
  }, []);

  const handleChange = (e) => {
    setNewTrip({ ...newTrip, [e.target.name]: e.target.value });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const addedTrip = await addTrip(newTrip);
    setTrips([...trips, addedTrip]);
    setNewTrip({ route: '', vehicle: '', driver: '', status: '' });
  };

  return (
    <div>
      <h2>Trips Management</h2>
      <form onSubmit={handleSubmit}>
        <input
          type="text"
          name="route"
          placeholder="Route"
          value={newTrip.route}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="vehicle"
          placeholder="Vehicle"
          value={newTrip.vehicle}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="driver"
          placeholder="Driver"
          value={newTrip.driver}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="status"
          placeholder="Status"
          value={newTrip.status}
          onChange={handleChange}
          required
        />
        <button type="submit">Add Trip</button>
      </form>
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Route</th>
            <th>Vehicle</th>
            <th>Driver</th>
            <th>Status</th>
          </tr>
        </thead>
        <tbody>
          {trips.map((trip) => (
            <tr key={trip.id}>
              <td>{trip.id}</td>
              <td>{trip.route}</td>
              <td>{trip.vehicle}</td>
              <td>{trip.driver}</td>
              <td>{trip.status}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default TripsList;
