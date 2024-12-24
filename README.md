# Fleet Management Application

A comprehensive fleet management application with frontend and backend components. This guide explains how to compile the code, set up the database, and deploy the application on AWS Kubernetes Service (EKS).

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
