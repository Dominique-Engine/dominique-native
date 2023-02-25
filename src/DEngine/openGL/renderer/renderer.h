#include <dengine/openGL/coreGL.h>
#include <vector>

namespace de {
namespace core {
void DrawPrimitive(RenderDataGL &data);
void FillGeometryBuffers(std::vector<float> &vertices,
                         std::vector<unsigned int> &indices, GLuint &vaoID,
                         GLuint &vboID, GLuint &eboID);
void LoadTexture(std::string path, GLuint &textureId,
                 FilterType filterType = FilterType::Lineal);
void CreateShader(Shader *shader, const char *vertexShaderSource,
                  const char *fragmentShaderSource);
// utility uniform functions
void SetShaderUniformBool(Shader *shader, const std::string &name, bool value);
void SetShaderUniformInt(Shader *shader, const std::string &name, int value);
void SetShaderUniformFloat(Shader *shader, const std::string &name,
                           float value);
}  // namespace core
}  // namespace de
