#include <dengine/openGL/coreGL.h>
#include <vector>
#include "dengine/components/types.hpp"

namespace de {
namespace core {

using namespace de::components;

void DrawPrimitive(RenderDataGL &data);
void FillGeometryBuffers(std::vector<float> &vertices,
                         std::vector<unsigned int> &indices, DEuint &vaoID,
                         DEuint &vboID, DEuint &eboID);
void LoadTexture(std::string path, DEuint &textureId,
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
