#include <dengine/core.h>

typedef unsigned int GLuint;

struct Shader {
  GLuint shaderProgram;
  GLuint vertexShader;
  GLuint fragmentShader;
};

struct RenderData {
  Shader shader;
  int test{100};
  GLuint vaoID[1];  // Our Vertex Array Object
  GLuint vboID[1];  // Our Vertex Buffer Object
};

namespace dengine {
namespace core {
// OpenGL related
int InitGL(DE &engine);
int CleanGL(DE &engine);
void RenderGL(DE &engine, const RenderData &data);
std::function<void(DE &)> SetupRendererGL(DE &engine);

}  // namespace core
}  // namespace dengine