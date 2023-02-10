#if !defined(DENGINE_CORE)
#define DENGINE_CORE

#include <functional>

#include "Drawable/drawable.h"

typedef struct SDL_Window SDL_Window;
typedef void *SDL_GLContext;

namespace DEngine
{
    enum class RendererType{
        OpenGl,
        DirectX11,
        Vulkan
    };

    struct DEConfig{
        float clearColor[4];
        char* title;
        int width;
        int height;
        int flags;
    };

    struct DE {
        RendererType rendererType;
        SDL_Window *windowHandler = nullptr;
        SDL_GLContext glContext;
        DEConfig config = {0.03f, 0.69f, 0.48f, 0.0f };
        std::vector<DrawableObject> drawables;
    };

    namespace Core
    {
        //OpenGl related
        int Init(DE &engine);
        int Clean(DE &engine);
        void Render(DE &engine);
        void Run(DE &engine);
    };
 
} // namespace DEngine




#endif // DENGINE_CORE
