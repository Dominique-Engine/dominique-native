#include <sstream>
#include <fstream>
#include <dengine/spdlog_helper.h>
#include "fileLoader.h"

// Loads file content to a string
bool de::utils::LoadFileToString(const std::string& path,
                                 std::string& content) {
  std::ifstream file(path.c_str());
  if (!file.is_open()) {
    getMultiSinkLogger().error("Could not open file: {}", path);
    return false;
  }
  std::stringstream ss;
  ss << file.rdbuf();
  content = ss.str();

  return true;
}