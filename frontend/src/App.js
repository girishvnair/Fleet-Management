import React from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';
import HomePage from './pages/HomePage';
import LoginPage from './pages/LoginPage';
import ReportsPage from './pages/ReportsPage';
import VehiclesList from './components/Vehicles/VehiclesList';
import TripsList from './components/Trips/TripsList';
import FuelLogs from './components/FuelLogs/FuelLogs';
import MaintenanceLogs from './components/MaintenanceLogs/MaintenanceLogs';
import ComplianceRecords from './components/Compliance/ComplianceRecords';
import Dashboard from './components/Dashboard/Dashboard';


const App = () => {
  return (
    <Router>
      <nav>
        <Link to="/">Home</Link> |
        <Link to="/dashboard">Dashboard</Link> |
        <Link to="/login">Login</Link> |
        <Link to="/reports">Reports</Link> |
        <Link to="/vehicles">Vehicles</Link> |
        <Link to="/trips">Trips</Link> |
        <Link to="/fuel-logs">Fuel Logs</Link> |
        <Link to="/maintenance">Maintenance Logs</Link> |
        <Link to="/compliance">Compliance Records</Link>
      </nav>

    <Routes>
      <Route path="/" element={<HomePage />} />
      <Route path="/login" element={<LoginPage />} />
      <Route path="/reports" element={<ReportsPage />} />
      <Route path="/vehicles" element={<VehiclesList />} />
      <Route path="/trips" element={<TripsList />} />
      <Route path="/fuel-logs" element={<FuelLogs />} />
      <Route path="/maintenance" element={<MaintenanceLogs />} />
      <Route path="/compliance" element={<ComplianceRecords />} />
      <Route path="/dashboard" element={<Dashboard />} />
    </Routes>

    </Router>
  );
};

export default App;
