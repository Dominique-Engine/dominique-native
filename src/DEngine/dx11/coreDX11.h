#include <d3d11.h>
#include <dengine/core.h>

#include "dx11_helpers.h"

namespace dengine {

namespace core {
// DirectX11 related
int InitDX11(DE &engine);
int CleanDX11(DE &engine);
void RenderDX11(DE &engine);
std::function<void(DE &engine)> SetupRendererDX11(DE &engine);
}  // namespace core
}  // namespace dengine