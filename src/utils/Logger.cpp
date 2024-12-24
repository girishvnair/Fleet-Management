#include "utils/Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex>

// Static member initialization
std::string Logger::logFile = "app.log";
std::string Logger::logLevel = "INFO";
std::mutex Logger::logMutex;

void Logger::init(const std::string& filePath, const std::string& level) {
    logFile = filePath;
    logLevel = level;
}

void Logger::log(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);

    // Get current time
    std::time_t now = std::time(nullptr);
    char timeStr[20];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Construct log message
    std::string logMessage = "[" + std::string(timeStr) + "] [" + level + "] " + message;

    // Write to file
    std::ofstream logFileStream(logFile, std::ios::app);
    if (logFileStream.is_open()) {
        logFileStream << logMessage << std::endl;
    } else {
        // Fallback to console if file writing fails
        std::cerr << "Logger Error: Unable to write to log file. Logging to console instead." << std::endl;
        std::cout << logMessage << std::endl;
    }

    logFileStream.close();
}

void Logger::info(const std::string& message) {
    if (logLevel == "INFO" || logLevel == "DEBUG") {
        log("INFO", message);
    }
}

void Logger::debug(const std::string& message) {
    if (logLevel == "DEBUG") {
        log("DEBUG", message);
    }
}

void Logger::error(const std::string& message) {
    log("ERROR", message);
}
