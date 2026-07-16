#pragma once

#include <string>

class DE_Logger {
  static int log_level;

  static void setLogLevel(int level);

  static void print(const std::string &message, int level);

  public:
    static void debug(const std::string &message);

    static void info(const std::string &message);

    static void warn(const std::string &message);

    static void error(const std::string &message);
};
