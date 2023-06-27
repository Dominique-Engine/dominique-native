#pragma once

#include "types.hpp"

namespace de {
namespace components {

// WIP
struct Camera {
  // View
  Vec3 eye{0.0f, -3.0f, -3.0f};
  Vec3 target{0.0f, 0.0f, 0.0f};
  Vec3 up{0.0f, 0.0f, 0.0f};

  // Projection
  float fov = 45.0f;
  float near = 0.1f;
  float far = 100.0f;
};

}  // namespace components
}  // namespace de