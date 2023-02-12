#include <d3d11.h>
#include <dengine/core.h>

#include "dx11_helpers.h"

namespace dengine {
namespace core {
// DirectX11 related
typedef unsigned int GLuintx;

struct ShaderDX11 {
  GLuintx shaderProgram;
  GLuintx vertexShader;
  GLuintx fragmentShader;
};

struct RenderDataDX11 {
  ShaderDX11 shader;
  int test{100};
  GLuintx vaoID[1];  // Our Vertex Array Object
  GLuintx vboID[1];  // Our Vertex Buffer Object
};
int InitDX11(DE &engine);
int CleanDX11(DE &engine);
void RenderDX11(DE &engine, const RenderDataDX11 &data);
std::function<void(DE &engine)> SetupRendererDX11(DE &engine);
}  // namespace core
}  // namespace dengine