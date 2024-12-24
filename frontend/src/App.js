import React from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';
import HomePage from './pages/HomePage';
import LoginPage from './pages/LoginPage';
import ReportsPage from './pages/ReportsPage';
import VehiclesList from './components/Vehicles/VehiclesList'; // Import the VehiclesList component

const App = () => {
  return (
    <Router>
      <nav>
        <Link to="/">Home</Link> | <Link to="/login">Login</Link> | <Link to="/reports">Reports</Link> | <Link to="/vehicles">Vehicles</Link>
      </nav>
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/login" element={<LoginPage />} />
        <Route path="/reports" element={<ReportsPage />} />
        <Route path="/vehicles" element={<VehiclesList />} /> {/* New Vehicles route */}
      </Routes>
    </Router>
  );
};

export default App;
