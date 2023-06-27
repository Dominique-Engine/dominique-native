#pragma once
#include <iostream>

namespace de {
namespace utils {
// Loads file content to a string
bool LoadFileToString(const std::string& path, std::string& content);

bool LoadGLTF(const std::string& path);
bool LoadObj(const std::string& path);

}  // namespace utils
}  // namespace de