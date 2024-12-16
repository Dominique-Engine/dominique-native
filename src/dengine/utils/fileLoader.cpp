#include "fileLoader.h"

#include <dengine/spdlog_helper.h>

#include <format>
#include <fstream>
#include <sstream>

#include "cgltf/cgltf.h"

using namespace de::utils::logger;

// Loads file content to a string
bool de::utils::LoadFileToString(const std::string& path,
                                 std::string& content) {
  std::ifstream file(path.c_str());
  if (!file.is_open()) {
    Logger::error(std::format("Could not open file: {}", path));
    return false;
  }
  std::stringstream ss;
  ss << file.rdbuf();
  content = ss.str();

  return true;
}

// Loads file content to a string
bool de::utils::LoadGLTF(const std::string& path) {
  cgltf_options options = {};
  cgltf_data* data = NULL;
  cgltf_result result = cgltf_parse_file(&options, path.c_str(), &data);
  if (result == cgltf_result_success) {
    /* TODO make awesome stuff */
    cgltf_free(data);
  }
  return true;
}

// Loads file content to a string
bool de::utils::LoadObj(const std::string& path) { return true; }