#pragma once

#include <string>
#include "types.hpp"

namespace de {
namespace components {

struct Material {
  std::string Name;

  float Ambient[3];
  float Diffuse[3];
  float Specular[3];
  float Shininess;
  DEuint DiffuseMapID;
};

struct DiffuseMap {
  DEuint DiffuseMapTO;
};

}  // namespace components
}  // namespace de