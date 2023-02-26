#pragma once

#include "types.hpp"

namespace de {
namespace components {

// WIP
struct camera {
  // View
  Vec3 eye;
  Vec3 target;
  Vec3 up;

  // Projection
  float fov = 45.0f;
  float near = 0.1f;
  float far = 100.0f;
};

}  // namespace components
}  // namespace de