#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>

struct Config {
    std::string appName;
    std::string version;
    std::string loggingLevel;
    std::string logFile;
    std::string databaseType;
    std::string databaseConnectionString;
};

class ConfigLoader {
public:
    // Loads the configuration from a JSON file
    static Config loadConfig(const std::string& filePath);
};

#endif // CONFIG_LOADER_H
