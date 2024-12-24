import React, { useEffect, useState } from 'react';
import { fetchComplianceRecords, addComplianceRecord, deleteComplianceRecord } from '../../utils/api';

const ComplianceRecords = () => {
  const [records, setRecords] = useState([]);
  const [newRecord, setNewRecord] = useState({
    vehicle: '',
    date: '',
    description: '',
  });

  useEffect(() => {
    const getRecords = async () => {
      const data = await fetchComplianceRecords();
      setRecords(data);
    };
    getRecords();
  }, []);

  const handleChange = (e) => {
    setNewRecord({ ...newRecord, [e.target.name]: e.target.value });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    const addedRecord = await addComplianceRecord(newRecord);
    setRecords([...records, addedRecord]);
    setNewRecord({ vehicle: '', date: '', description: '' });
  };

  const handleDelete = async (id) => {
    await deleteComplianceRecord(id);
    setRecords(records.filter((record) => record.id !== id));
  };

  return (
    <div>
      <h2>Compliance Records</h2>
      <form onSubmit={handleSubmit}>
        <input
          type="text"
          name="vehicle"
          placeholder="Vehicle"
          value={newRecord.vehicle}
          onChange={handleChange}
          required
        />
        <input
          type="date"
          name="date"
          placeholder="Date"
          value={newRecord.date}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="description"
          placeholder="Description"
          value={newRecord.description}
          onChange={handleChange}
          required
        />
        <button type="submit">Add Record</button>
      </form>
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Vehicle</th>
            <th>Date</th>
            <th>Description</th>
            <th>Actions</th>
          </tr>
        </thead>
        <tbody>
          {records.map((record) => (
            <tr key={record.id}>
              <td>{record.id}</td>
              <td>{record.vehicle}</td>
              <td>{record.date}</td>
              <td>{record.description}</td>
              <td>
                <button onClick={() => handleDelete(record.id)}>Delete</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default ComplianceRecords;
