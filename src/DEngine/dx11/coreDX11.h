#include <d3d11.h>
#include <dengine/core.h>

#include "dx11_helpers.h"

#include "DirectXMath.h"

namespace dengine {
namespace core {
// DirectX11 related
struct ShaderDX11 {
  ID3D11VertexShader *p_vertexShader;
  ID3D11PixelShader *p_pixelShader;
};

// temporal, just for testing and learning, in future all this kind of
// structures should be centralized
struct VertexPositionColor {
  DirectX::XMFLOAT3 pos;
  DirectX::XMFLOAT3 color;
};

struct RenderDataDX11 {
  ShaderDX11 shader;
  ID3D11Buffer *vertexBuffer;
  ID3D11Buffer *indexBuffer;
  uint64_t indexCount;
  // GLuintx vaoID[1];  // Our Vertex Array Object
  // GLuintx vboID[1];  // Our Vertex Buffer Object
};
int InitDX11(DE &engine);
int CleanDX11(DE &engine);
void RenderDX11(DE &engine, const RenderDataDX11 &data);
std::function<void(DE &engine)> SetupRendererDX11(DE &engine);

// Helpers and primitives
int CreateCube(dengine::core::RenderDataDX11 &data);
}  // namespace core
}  // namespace dengine