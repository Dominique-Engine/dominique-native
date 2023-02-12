#include <dengine/core.h>

namespace dengine {
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
  int test{100};
  GLuint vaoID[1];  // Our Vertex Array Object
  GLuint vboID[1];  // Our Vertex Buffer Object
};

int InitGL(DE &engine);
int CleanGL(DE &engine);
void RenderGL(DE &engine, const RenderDataGL &data);
std::function<void(DE &)> SetupRendererGL(DE &engine);

}  // namespace core
}  // namespace dengine