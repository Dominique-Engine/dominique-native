#include <dengine/core.h>
#include <vector>

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
  GLuint vaoID;  // Our Vertex Array Object
  GLuint vboID;  // Our Vertex Buffer Object
};

int InitGL(DE &engine);
int CleanGL(DE &engine);
void RenderGL(DE &engine, const std::vector<RenderDataGL> &data);
std::function<void(DE &)> SetupRendererGL(DE &engine);

}  // namespace core
}  // namespace dengine