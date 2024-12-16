#include "spdlog_helper.h"

#include <iostream>
#include <string>

int de::utils::logger::Logger::log_level = 0;

void de::utils::logger::Logger::setLogLevel(int level) { log_level = level; }

void de::utils::logger::Logger::print(const std::string& message, int level) {
  if (level >= log_level) {
    std::cout << message << std::endl;
  }
}

void de::utils::logger::Logger::debug(const std::string& message) {
  print(message, 0);
}

void de::utils::logger::Logger::info(const std::string& message) {
  print(message, 1);
}

void de::utils::logger::Logger::warn(const std::string& message) {
  print(message, 2);
}

void de::utils::logger::Logger::error(const std::string& message) {
  print(message, 3);
}
