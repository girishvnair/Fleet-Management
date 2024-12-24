import React, { useEffect, useState } from 'react';
import { fetchDashboardMetrics } from '../../utils/api';

const Dashboard = () => {
  const [metrics, setMetrics] = useState(null);

  useEffect(() => {
    const getMetrics = async () => {
      const data = await fetchDashboardMetrics();
      setMetrics(data);
    };
    getMetrics();
  }, []);

  if (!metrics) return <div>Loading...</div>;

  return (
    <div>
      <h2>Dashboard</h2>
      <div>Active Vehicles: {metrics.activeVehicles}</div>
      <div>Trip Statuses: Completed - {metrics.tripStatuses.completed}, Ongoing - {metrics.tripStatuses.ongoing}</div>
      <div>Total Fuel Consumption: {metrics.totalFuelConsumption} liters</div>
      <div>Maintenance Alerts: {metrics.maintenanceAlerts}</div>
    </div>
  );
};

export default Dashboard;
