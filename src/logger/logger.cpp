#include "./logger.h"

#include <iostream>
#include <string>

int DE_Logger::log_level = 0;

void DE_Logger::setLogLevel(int level) { log_level = level; }

void DE_Logger::print(const std::string& message, int level) {
  if (level >= log_level) {
    std::cout << message << std::endl;
  }
}

void DE_Logger::debug(const std::string& message) {
  print(message, 0);
}

void DE_Logger::info(const std::string& message) {
  print(message, 1);
}

void DE_Logger::warn(const std::string& message) {
  print(message, 2);
}

void DE_Logger::error(const std::string& message) {
  print(message, 3);
}
