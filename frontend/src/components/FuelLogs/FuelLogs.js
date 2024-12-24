import React, { useEffect, useState } from 'react';
import { fetchFuelLogs, addFuelLog, deleteFuelLog } from '../../utils/api';

const FuelLogs = () => {
  const [fuelLogs, setFuelLogs] = useState([]);
  const [newFuelLog, setNewFuelLog] = useState({
    vehicle: '',
    date: '',
    quantity: '',
    cost: '',
  });

  useEffect(() => {
    const getFuelLogs = async () => {
      const data = await fetchFuelLogs();
      setFuelLogs(data);
    };
    getFuelLogs();
  }, []);

  const handleChange = (e) => {
    setNewFuelLog({ ...newFuelLog, [e.target.name]: e.target.value });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const addedLog = await addFuelLog(newFuelLog);
    setFuelLogs([...fuelLogs, addedLog]);
    setNewFuelLog({ vehicle: '', date: '', quantity: '', cost: '' });
  };

  const handleDelete = async (id) => {
    await deleteFuelLog(id);
    setFuelLogs(fuelLogs.filter((log) => log.id !== id));
  };

  return (
    <div>
      <h2>Fuel Logs</h2>
      <form onSubmit={handleSubmit}>
        <input type="text" name="vehicle" placeholder="Vehicle" value={newFuelLog.vehicle} onChange={handleChange} required />
        <input type="date" name="date" placeholder="Date" value={newFuelLog.date} onChange={handleChange} required />
        <input type="number" name="quantity" placeholder="Quantity" value={newFuelLog.quantity} onChange={handleChange} required />
        <input type="number" name="cost" placeholder="Cost" value={newFuelLog.cost} onChange={handleChange} required />
        <button type="submit">Add Log</button>
      </form>
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Vehicle</th>
            <th>Date</th>
            <th>Quantity</th>
            <th>Cost</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {fuelLogs.map((log) => (
            <tr key={log.id}>
              <td>{log.id}</td>
              <td>{log.vehicle}</td>
              <td>{log.date}</td>
              <td>{log.quantity}</td>
              <td>{log.cost}</td>
              <td>
                <button onClick={() => handleDelete(log.id)}>Delete</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default FuelLogs;
