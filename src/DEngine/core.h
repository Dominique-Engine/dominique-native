#if !defined(DENGINE_CORE)
#define DENGINE_CORE

#include <SDL2/SDL.h>


namespace DEngine
{
    class Core
    {
    private:
        bool isRunning;
        SDL_Window* windowHandler;
        SDL_GLContext glContext;
    public:
        Core(/* args */);
        ~Core();
        int Init(const char* title, const int &width, const int &height, const int &flags = 0);
        int Clean();
        void Render();

        SDL_Window* getSDLwinHandler();
        SDL_GLContext getSDLglContext();

    };
 
} // namespace DEngine




#endif // DENGINE_CORE
