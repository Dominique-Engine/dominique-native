#include <dengine/core.h>
#include <vector>
#include <functional>
#include "dengine/components/types.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace de::core {
using namespace de::components;

struct RenderTarget {
  glm::mat4 model{1.0f};
  glm::mat4 projection{1.0f};
  glm::mat4 view{1.0f};
};

struct Shader {
  DEuint shaderProgram;
  DEuint vertexShader;
  DEuint fragmentShader;
};

struct RenderData {
  Shader shader;
  DEuint vaoID; // Vertex Array Object
  DEuint eboID; // Element Array Object
  DEuint vboID; // Vertex Buffer Object
  std::vector<DEuint> textures;
  int vertexNumber;
  glm::mat4 trans{1.0f};
};

namespace sdl_gpu {
// OpenGL related

enum class FilterType {
  Lineal,
  Point,
};

int Init(DE &engine);

int Clean(DE &engine);

void Render(DE &engine,
            de::ecs::Scene &scene,
            de::core::RenderTarget &target,
            const std::vector<de::core::RenderData> &data);

std::function<void(de::DE &, de::ecs::Scene &, de::core::RenderTarget &)>
SetupRenderer(DE &engine, de::ecs::Scene &scene);
} // namespace sdl_gpu
} // namespace de::core
