#if !defined(DE_SDL_HELPER)
#define DE_SDL_HELPER


#include <SDL2/SDL.h>
#include "spdlog_helper.h"

void logSDL2renderersInfo()
{
    auto logger = getMultiSinkLogger();

    auto a = SDL_GetNumRenderDrivers();
    logger.info("Number of SDL devices: {}, with info:", a );
    {
        SDL_RendererInfo temp;
        for (short i = 0; i < a; i++)
        {
            SDL_GetRenderDriverInfo(i, &temp );
            logger.info("name: {}, max texture height: {}, max texture width: {}, num texture formats: {}", 
                temp.name, temp.max_texture_height, temp.max_texture_width, temp.num_texture_formats );
        }
    }
}


#endif // DE_SDL_HELPER
