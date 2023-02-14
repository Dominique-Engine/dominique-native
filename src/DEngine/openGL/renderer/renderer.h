#include <dengine/openGL/coreGL.h>
#include <vector>

namespace dengine {
namespace core {
void DrawPrimitive(GLuint vaoID, GLuint vboID, Shader shader);
void FillGeometryBuffers(std::vector<float> &vertices, GLuint &vaoID,
                         GLuint &vboID);
void CreateShader(Shader *shader, const char *vertexShaderSource,
                  const char *fragmentShaderSource);
}  // namespace core
}  // namespace dengine
