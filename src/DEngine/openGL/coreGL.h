#include <dengine/core.h>

namespace dengine {

namespace core {
// DirectX11 related
int InitGL(DE &engine);
int CleanGL(DE &engine);
void RenderGL(DE &engine);
void SetupRenderer(DE &engine);
}  // namespace core
}  // namespace dengine