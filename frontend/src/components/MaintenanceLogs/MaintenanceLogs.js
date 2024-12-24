import React, { useEffect, useState } from 'react';
import { fetchMaintenanceLogs, addMaintenanceLog, deleteMaintenanceLog } from '../../utils/api';

const MaintenanceLogs = () => {
  const [logs, setLogs] = useState([]);
  const [newLog, setNewLog] = useState({
    vehicle: '',
    date: '',
    description: '',
    cost: '',
  });

  useEffect(() => {
    const getLogs = async () => {
      const data = await fetchMaintenanceLogs();
      setLogs(data);
    };
    getLogs();
  }, []);

  const handleChange = (e) => {
    setNewLog({ ...newLog, [e.target.name]: e.target.value });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const addedLog = await addMaintenanceLog(newLog);
    setLogs([...logs, addedLog]);
    setNewLog({ vehicle: '', date: '', description: '', cost: '' });
  };

  const handleDelete = async (id) => {
    await deleteMaintenanceLog(id);
    setLogs(logs.filter((log) => log.id !== id));
  };

  return (
    <div>
      <h2>Maintenance Logs</h2>
      <form onSubmit={handleSubmit}>
        <input type="text" name="vehicle" placeholder="Vehicle" value={newLog.vehicle} onChange={handleChange} required />
        <input type="date" name="date" placeholder="Date" value={newLog.date} onChange={handleChange} required />
        <input type="text" name="description" placeholder="Description" value={newLog.description} onChange={handleChange} required />
        <input type="number" name="cost" placeholder="Cost" value={newLog.cost} onChange={handleChange} required />
        <button type="submit">Add Log</button>
      </form>
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Vehicle</th>
            <th>Date</th>
            <th>Description</th>
            <th>Cost</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {logs.map((log) => (
            <tr key={log.id}>
              <td>{log.id}</td>
              <td>{log.vehicle}</td>
              <td>{log.date}</td>
              <td>{log.description}</td>
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

export default MaintenanceLogs;
