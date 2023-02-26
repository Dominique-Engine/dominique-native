#pragma once

#include "types.hpp"
#include <string>
#include <vector>

namespace de {
namespace components {

// WIP
struct Mesh {
  std::string name;

  DEuint vaoID;   // vertices array object
  DEuint pboID;   // position buffer object
  DEuint tcboID;  // texture coordinates buffer object
  DEuint nboID;   // normals buffer object
  DEuint iboID;   // index buffer object

  DEuint indexCount;
  DEuint vertexCount;

  std::vector<DEuint> matIDs;  // material ids
};

}  // namespace components
}  // namespace de