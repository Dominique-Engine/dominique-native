#include <dengine/core.h>
#include <vector>
#include <functional>

namespace de {
namespace core {
typedef unsigned int GLuint;
// OpenGL related
struct Shader {
  GLuint shaderProgram;
  GLuint vertexShader;
  GLuint fragmentShader;
};

struct RenderDataGL {
  Shader shader;
  GLuint vaoID;  // Vertex Array Object
  GLuint eboID;  // Element Array Object
  GLuint vboID;  // Vertex Buffer Object
  std::vector<GLuint> textures;
  int vertexNumber;
};

enum class FilterType {
  Lineal,
  Point,
};

int InitGL(DE &engine);
int CleanGL(DE &engine);
void RenderGL(DE &engine, const std::vector<RenderDataGL> &data);
std::function<void(DE &)> SetupRendererGL(DE &engine, de::ecs::Scene &scene);

}  // namespace core
}  // namespace de