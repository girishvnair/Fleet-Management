#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>

class Logger {
public:
    // Initializes the logger with a log file path and log level
    static void init(const std::string& filePath, const std::string& level);

    // Logs an informational message
    static void info(const std::string& message);

    // Logs a debug message
    static void debug(const std::string& message);

    // Logs an error message
    static void error(const std::string& message);

private:
    static std::string logFile;
    static std::string logLevel;
    static std::mutex logMutex;

    // Internal method to log a message with a specific level
    static void log(const std::string& level, const std::string& message);
};

#endif // LOGGER_H
