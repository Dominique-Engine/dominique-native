#if !defined(DE_SDL_HELPER)
#define DE_SDL_HELPER

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <stb/stb_image.h>

#include "spdlog_helper.h"
namespace de {

void logSDL2renderersInfo();

// From https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
SDL_Surface* loadImgFromFile2SDLSurface(const char* filename,
                                        const int req_format = STBI_rgb_alpha);

}  // namespace de

#endif  // DE_SDL_HELPER
