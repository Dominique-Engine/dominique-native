#pragma once
#include <iostream>

namespace de {
namespace utils {
// Loads file content to a string
bool LoadFileToString(const std::string& path, std::string& content);

}  // namespace utils
}  // namespace de