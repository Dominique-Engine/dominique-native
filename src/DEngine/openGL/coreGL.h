#include <dengine/core.h>
#include <vector>
#include <functional>
#include "dengine/components/types.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace de {
namespace core {

using namespace de::components;

// OpenGL related
struct Shader {
  DEuint shaderProgram;
  DEuint vertexShader;
  DEuint fragmentShader;
};

struct RenderDataGL {
  Shader shader;
  DEuint vaoID;  // Vertex Array Object
  DEuint eboID;  // Element Array Object
  DEuint vboID;  // Vertex Buffer Object
  std::vector<DEuint> textures;
  int vertexNumber;
  glm::mat4 trans{1.0f};
};

struct RenderTargetGL {
  glm::mat4 model{1.0f};
  glm::mat4 projection{1.0f};
  glm::mat4 view{1.0f};
};

enum class FilterType {
  Lineal,
  Point,
};

int InitGL(DE &engine);
int CleanGL(DE &engine);
void RenderGL(DE &engine, de::ecs::Scene &scene,
              de::core::RenderTargetGL &target,
              const std::vector<de::core::RenderDataGL> &data);
std::function<void(de::DE &, de::ecs::Scene &, de::core::RenderTargetGL &)>
SetupRendererGL(DE &engine, de::ecs::Scene &scene);

}  // namespace core
}  // namespace de