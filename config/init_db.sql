-- Create a table for users
CREATE TABLE IF NOT EXISTS Users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
);

-- Create a table for vehicles
CREATE TABLE IF NOT EXISTS Vehicles (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    license_plate TEXT UNIQUE NOT NULL,
    make TEXT NOT NULL,
    model TEXT NOT NULL,
    year INTEGER NOT NULL,
    status TEXT NOT NULL DEFAULT 'Available'
);

-- Create a table for trips
CREATE TABLE IF NOT EXISTS Trips (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vehicle_id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    start_time DATETIME NOT NULL,
    end_time DATETIME,
    start_location TEXT NOT NULL,
    end_location TEXT,
    FOREIGN KEY (vehicle_id) REFERENCES Vehicles (id),
    FOREIGN KEY (user_id) REFERENCES Users (id)
);

-- Create a table for maintenance logs
CREATE TABLE IF NOT EXISTS MaintenanceLogs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vehicle_id INTEGER NOT NULL,
    date DATETIME NOT NULL,
    description TEXT NOT NULL,
    FOREIGN KEY (vehicle_id) REFERENCES Vehicles (id)
);

-- Create a table for fuel logs
CREATE TABLE IF NOT EXISTS FuelLogs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vehicle_id INTEGER NOT NULL,
    date DATETIME NOT NULL,
    fuel_amount REAL NOT NULL,
    cost REAL NOT NULL,
    FOREIGN KEY (vehicle_id) REFERENCES Vehicles (id)
);

CREATE TABLE IF NOT EXISTS ComplianceRecords (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    vehicle_id INTEGER NOT NULL,
    type TEXT NOT NULL,
    date DATETIME NOT NULL,
    description TEXT NOT NULL,
    FOREIGN KEY (vehicle_id) REFERENCES Vehicles (id)
);

