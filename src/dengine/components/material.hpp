#pragma once

#include <string>

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
