# Fleet Management Application

A comprehensive fleet management application with frontend and backend components. This guide explains how to compile the code, set up the database, and deploy the application on AWS Kubernetes Service (EKS).

---

## Features

### Core Features:
1. **User Management**:
   - Add, authenticate, and remove users.

2. **Vehicle Management**:
   - Add new vehicles with attributes like license plate, make, model, year, and status.
   - Update the status of vehicles (e.g., Available, In Maintenance, In Use).
   - Retrieve a list of all vehicles.

3. **Trip Management**:
   - Start and end trips with information such as vehicle ID, user ID, start and end times, and locations.
   - Retrieve all trips, including their details.

4. **Fuel Log Management**:
   - Add fuel logs with details like vehicle ID, date, fuel amount, and cost.
   - Retrieve all fuel logs or logs for a specific vehicle.

5. **Maintenance Log Management**:
   - Add maintenance logs with attributes like vehicle ID, date, and description.
   - Retrieve maintenance logs for a specific vehicle or all logs.

6. **Compliance Records Management**:
   - Add compliance records with details like type (e.g., Inspection, Certification), date, and description.
   - Retrieve compliance records for specific vehicles or all compliance records.

7. **Dashboard Metrics** (Frontend Feature):
   - Provides a summary view with metrics like active vehicles, completed trips, ongoing trips, fuel consumption, and maintenance alerts.

### Frontend Features:
1. **React-Based UI**:
   - User-friendly interfaces for managing vehicles, trips, fuel logs, maintenance logs, and compliance records.
   - Navigation through pages like Dashboard, Reports, Vehicles, and Trips.

2. **Data Interaction**:
   - Ability to add, edit, delete, and view records via forms and tables.

3. **Reports**:
   - Generate and download reports in PDF and Excel formats.

4. **Authentication**:
   - Basic login functionality.

### Backend Features:
1. **Database Integration**:
   - Uses SQLite for data storage.
   - Structured database schema for users, vehicles, trips, fuel logs, maintenance logs, and compliance records.

2. **API Endpoints**:
   - RESTful API for communication between the frontend and backend.

3. **Logging**:
   - Centralized logging mechanism using a Logger class.

4. **Configuration Management**:
   - Configuration handled via JSON files for settings like database connection and logging levels.

5. **Unit Testing**:
   - Unit tests for core managers like `VehicleManager`, `FuelLogManager`, `MaintenanceLogManager`, `ComplianceManager`, `TripManager`, and `UserManager`.

---

---

## Prerequisites

1. **AWS CLI Installed**  
   Install and configure AWS CLI with your credentials:
   ```bash
   aws configure
   ```

2. **kubectl Installed**  
   Install kubectl to manage the Kubernetes cluster:
   ```bash
   curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
   chmod +x kubectl
   sudo mv kubectl /usr/local/bin/
   ```

3. **eksctl Installed**  
   Install eksctl to create and manage the EKS cluster:
   ```bash
   brew tap weaveworks/tap
   brew install weaveworks/tap/eksctl
   ```

4. **Docker Installed**  
   Install Docker for building and pushing images:
   ```bash
   sudo apt-get install docker.io
   ```

5. **GitHub Repository Access**  
   Clone your repository locally:
   ```bash
   git clone https://github.com/<your-username>/Fleet-Management.git
   cd Fleet-Management
   ```

---

## Backend Setup

### 1. Compile the Backend Code

1. Navigate to the backend directory:
   ```bash
   cd backend
   ```

2. Compile the C++ backend code:
   - Using `g++`:
     ```bash
     g++ -o backend main.cpp
     ```
   - Using `make` (if a Makefile is available):
     ```bash
     make
     ```

3. Start the backend server:
   ```bash
   ./backend
   ```

4. Ensure the backend server is running on `http://localhost:5000`.

### 2. Database Setup

If the backend requires a database, follow these steps:

1. **Install PostgreSQL**:
   ```bash
   sudo apt-get update
   sudo apt-get install postgresql postgresql-contrib
   ```

2. **Start PostgreSQL Service**:
   ```bash
   sudo service postgresql start
   ```

3. **Create a Database**:
   ```bash
   sudo -u postgres psql
   CREATE DATABASE fleet_management;
   \\q
   ```

4. **Update Backend Configuration**:
   Update the database connection string in the backend configuration file (e.g., `config.json` or `main.cpp`).

---

## Frontend Setup

### 1. Build the Frontend Code

1. Navigate to the frontend directory:
   ```bash
   cd frontend
   ```

2. Install dependencies:
   ```bash
   npm install
   ```

3. Build the Docker image:
   ```bash
   docker build -t fleet-frontend .
   ```

4. Push the Docker image to AWS ECR:
   ```bash
   docker tag fleet-frontend:latest <your-aws-account-id>.dkr.ecr.us-west-2.amazonaws.com/fleet-frontend:latest
   docker push <your-aws-account-id>.dkr.ecr.us-west-2.amazonaws.com/fleet-frontend:latest
   ```

5. Ensure all required npm packages are listed in `package.json` under `dependencies` and `devDependencies`. Add the following if needed:
   ```json
   "dependencies": {
     "react": "^19.0.0",
     "react-dom": "^19.0.0",
     "react-router-dom": "^7.1.1",
     "file-saver": "^2.0.5",
     "xlsx": "^0.18.5",
     "webpack": "^5.97.1",
     "webpack-cli": "^6.0.1",
     "html-webpack-plugin": "^5.6.3"
   },
   "devDependencies": {
     "babel-loader": "^9.1.2",
     "css-loader": "^7.1.2",
     "style-loader": "^4.0.0",
     "@babel/core": "^7.26.0",
     "@babel/preset-env": "^7.26.0",
     "@babel/preset-react": "^7.26.3"
   }
   ```

---

## Deploying to AWS Kubernetes (EKS)

### 1. Create an EKS Cluster

1. Create the EKS cluster:
   ```bash
   eksctl create cluster --name fleet-management-cluster --region us-west-2 --nodes 2
   ```

2. Verify the cluster is running:
   ```bash
   kubectl get nodes
   ```

### 2. Kubernetes Manifests

Create the following Kubernetes manifests in a `k8s/` directory:

#### Namespace
`namespace.yaml`
```yaml
apiVersion: v1
kind: Namespace
metadata:
  name: fleet-management
```

#### Backend Deployment and Service
`backend-deployment.yaml`
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: fleet-backend
  namespace: fleet-management
spec:
  replicas: 2
  selector:
    matchLabels:
      app: fleet-backend
  template:
    metadata:
      labels:
        app: fleet-backend
    spec:
      containers:
      - name: fleet-backend
        image: <your-aws-account-id>.dkr.ecr.us-west-2.amazonaws.com/fleet-backend:latest
        ports:
        - containerPort: 5000
```

`backend-service.yaml`
```yaml
apiVersion: v1
kind: Service
metadata:
  name: fleet-backend
  namespace: fleet-management
spec:
  selector:
    app: fleet-backend
  ports:
  - protocol: TCP
    port: 5000
    targetPort: 5000
  type: ClusterIP
```

#### Frontend Deployment and Service
`frontend-deployment.yaml`
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: fleet-frontend
  namespace: fleet-management
spec:
  replicas: 2
  selector:
    matchLabels:
      app: fleet-frontend
  template:
    metadata:
      labels:
        app: fleet-frontend
    spec:
      containers:
      - name: fleet-frontend
        image: <your-aws-account-id>.dkr.ecr.us-west-2.amazonaws.com/fleet-frontend:latest
        ports:
        - containerPort: 3000
```

`frontend-service.yaml`
```yaml
apiVersion: v1
kind: Service
metadata:
  name: fleet-frontend
  namespace: fleet-management
spec:
  selector:
    app: fleet-frontend
  ports:
      - protocol: TCP
        port: 80
        targetPort: 3000
      type: LoadBalancer
```

### 3. Deploy Manifests

1. Apply the namespace:
   ```bash
   kubectl apply -f k8s/namespace.yaml
   ```

2. Apply the backend manifests:
   ```bash
   kubectl apply -f k8s/backend-deployment.yaml
   kubectl apply -f k8s/backend-service.yaml
   ```

3. Apply the frontend manifests:
   ```bash
   kubectl apply -f k8s/frontend-deployment.yaml
   kubectl apply -f k8s/frontend-service.yaml
   ```

### 4. Verify Deployments

1. Check the status of pods:
   ```bash
   kubectl get pods -n fleet-management
   ```

2. Get the frontend LoadBalancer URL:
   ```bash
   kubectl get svc -n fleet-management
   ```
   Use the `EXTERNAL-IP` for the frontend service to access the application in your browser.

---

## Testing

1. Access the frontend URL from the LoadBalancer.
2. Navigate through the application (e.g., `/vehicles`, `/fuel-logs`).
3. Verify interactions with the backend.

---

## Optional Enhancements

- **Setup CI/CD Pipelines:** Automate builds and deployments using GitHub Actions.
- **Add Monitoring:** Use Prometheus and Grafana for application monitoring.
- **Secure APIs:** Use Kubernetes Secrets for sensitive configurations.

---

## Troubleshooting

- **CORS Errors:** Add appropriate headers in the backend.
- **Deployment Failures:** Check pod logs:
  ```bash
  kubectl logs <pod-name> -n fleet-management
  ```
- **Database Issues:** Verify PostgreSQL service is running and accessible.

---

Happy Deployment! 🚀
