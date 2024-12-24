#include "utils/ConfigLoader.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Config ConfigLoader::loadConfig(const std::string& filePath) {
    Config config;
    try {
        std::ifstream configFile(filePath);
        if (!configFile.is_open()) {
            throw std::runtime_error("Could not open config file: " + filePath);
        }

        json configJson;
        configFile >> configJson;

        config.appName = configJson.at("appName").get<std::string>();
        config.version = configJson.at("version").get<std::string>();
        config.loggingLevel = configJson.at("logging").at("level").get<std::string>();
        config.logFile = configJson.at("logging").at("file").get<std::string>();
        config.databaseType = configJson.at("database").at("type").get<std::string>();
        config.databaseConnectionString = configJson.at("database").at("connectionString").get<std::string>();
    } catch (const std::exception& e) {
        std::cerr << "Error loading configuration: " << e.what() << std::endl;
        throw;
    }
    return config;
}
