#if !defined(DE_SDL_HELPER)
#define DE_SDL_HELPER

#include <SDL2/SDL.h>
#include <stb/stb_image.h>

#include "spdlog_helper.h"
namespace dengine {

void logSDL2renderersInfo();

// From https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
SDL_Surface* loadImgFromFile2SDLSurface(const char* filename,
                                        const int req_format = STBI_rgb_alpha);

}  // namespace dengine

#endif  // DE_SDL_HELPER
