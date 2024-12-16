#define STB_IMAGE_IMPLEMENTATION  // TODO avoid this here to be able to use
// stb_image in more places easily
#include "sdl_helpers.h"

#include <format>

using namespace de::utils::logger;

void de::logSDL2renderersInfo() {
  auto a = SDL_GetNumRenderDrivers();
  Logger::info(std::format("Number of SDL devices: {}, with info:", a));
  {
    SDL_RendererInfo temp;
    for (short i = 0; i < a; i++) {
      SDL_GetRenderDriverInfo(i, &temp);
      Logger::info(std::format(
          "name: {}, max texture height: {}, max texture width: {}, num "
          "texture formats: {}",
          temp.name, temp.max_texture_height, temp.max_texture_width,
          temp.num_texture_formats));
    }
  }
  a = SDL_GetNumVideoDrivers();
  Logger::info(std::format("Number of SDL video drivers: {}, with names:", a));
  {
    for (short i = 0; i < a; i++) {
      Logger::info(std::format("name: {}", SDL_GetVideoDriver(i)));
    }
  }
}

// From https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
SDL_Surface *de::loadImgFromFile2SDLSurface(const char *filename,
                                            const int req_format) {
  int width, height, orig_format;
  unsigned char *data =
      stbi_load(filename, &width, &height, &orig_format, req_format);
  if (data == nullptr) {
    return nullptr;
  }

  // Set up the pixel format color masks for RGB(A) byte arrays.
  // Only STBI_rgb (3) and STBI_rgb_alpha (4) are supported here!
  Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  int shift = (req_format == STBI_rgb) ? 8 : 0;
  rmask = 0xff000000 >> shift;
  gmask = 0x00ff0000 >> shift;
  bmask = 0x0000ff00 >> shift;
  amask = 0x000000ff >> shift;
#else  // little endian, like x86
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
#endif

  int depth, pitch;
  if (req_format == STBI_rgb) {
    depth = 24;
    pitch = 3 * width;  // 3 bytes per pixel * pixels per row
  } else {              // STBI_rgb_alpha (RGBA)
    depth = 32;
    pitch = 4 * width;
  }

  return SDL_CreateRGBSurfaceFrom((void *)data, width, height, depth, pitch,
                                  rmask, gmask, bmask, amask);

  // TODO put this somewhere stbi_image_free(data); if needed
}