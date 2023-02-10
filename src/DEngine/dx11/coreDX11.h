#include <d3d11.h>
#include <DEngine/core.h>

#include "dx11_helpers.h"

namespace DEngine {

    namespace Core {
        //DirectX11 related
        int InitDX11(DE &engine);
        int CleanDX11(DE &engine);
        void RenderDX11(DE &engine);
    }
}