#if !defined(DENGINE_CORE)
#define DENGINE_CORE

#include <SDL2/SDL.h>
#include <functional>

#include <d3d11.h>

namespace DEngine
{
    enum class RendererType{
        OpenGl,
        DirectX11
    };


    struct DEDirectX11Context{
        // TODO this are COM interfaces(light COM), check if its better to put them in global scope as in DearImGui code
        ID3D11Device*            pd3dDevice = NULL;
        ID3D11DeviceContext*     pd3dDeviceContext = NULL;
        IDXGISwapChain*          pSwapChain = NULL;
        ID3D11RenderTargetView*  mainRenderTargetView = NULL;
    };

    struct DEConfig{
        float clearColor[4];
    };

    class Core
    {
    private:
        bool isRunning;
        const RendererType rendererType;
        //TODO maybe change this handlers for something like void*
        SDL_Window* windowHandler;
        SDL_GLContext glContext;
        DEDirectX11Context dxContext;
        DEConfig config = {0.0f, 0.5f, 1.0f, 0.0f };

        //OpenGl related
        int InitGL(const char* title, const int &width, const int &height, const int &flags = 0);
        int CleanGL();
        void RenderGL();

        //DirectX11 related
        int InitDX11(const char* title, const int &width, const int &height, const int &flags = 0);
        int CleanDX11();
        void RenderDX11();

    public:
        Core(const RendererType &rendererTypeValue);
        ~Core();
        Core(const Core& ) = delete;//remove copy constructor
        Core& operator=(const Core& ) = delete;// remove assignment operator 

        int Init(const char* title, const int &width, const int &height, const int &flags = 0);
        int Clean();
        void Render();

        SDL_Window* getSDLwinHandler();
        SDL_GLContext getSDLglContext();
        DEDirectX11Context getDX11Context();

    };
 
} // namespace DEngine




#endif // DENGINE_CORE
