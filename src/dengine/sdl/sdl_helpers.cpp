#define STB_IMAGE_IMPLEMENTATION  // TODO avoid this here to be able to use
// stb_image in more places easily
#include "sdl_helpers.h"

#include <cstring>
#include <format>


void de::logSDL2renderersInfo() {
  auto a = SDL_GetNumRenderDrivers();
  DE_Logger::info(std::format("Number of SDL devices: {}, with info:", a));
  {
    // SDL_RendererInfo temp;
    for (short i = 0; i < a; i++) {
      // SDL_GetRenderDriverInfo(i, &temp);
      // Logger::info(std::format(
      //     "name: {}, max texture height: {}, max texture width: {}, num "
      //     "texture formats: {}",
      //     temp.name, temp.max_texture_height, temp.max_texture_width,
      //     temp.num_texture_formats));
      DE_Logger::info(std::format("name: {}", SDL_GetRenderDriver(i)));
    }
  }
  a = SDL_GetNumVideoDrivers();
  DE_Logger::info(std::format("Number of SDL video drivers: {}, with names:", a));
  {
    for (short i = 0; i < a; i++) {
      DE_Logger::info(std::format("name: {}", SDL_GetVideoDriver(i)));
    }
  }
}

// From https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
SDL_Surface *de::loadImgFromFile2SDLSurface(const char *filename,
                                            const int req_format) {
  if (req_format != STBI_rgb && req_format != STBI_rgb_alpha) {
    DE_Logger::error("Unsupported image format request");
    return nullptr;
  }

  int width, height, orig_format;
  unsigned char *data =
      stbi_load(filename, &width, &height, &orig_format, req_format);
  if (data == nullptr) {
    return nullptr;
  }

  const int bytes_per_pixel = req_format == STBI_rgb ? 3 : 4;
  const int src_pitch = bytes_per_pixel * width;
  const SDL_PixelFormat format =
      req_format == STBI_rgb ? SDL_PIXELFORMAT_RGB24 : SDL_PIXELFORMAT_RGBA32;
  SDL_Surface *surface = SDL_CreateSurface(width, height, format);

  if (surface == nullptr) {
    DE_Logger::error("Could not create SDL surface");
    stbi_image_free(data);
    return nullptr;
  }

  const bool must_lock = SDL_MUSTLOCK(surface);
  if (must_lock && !SDL_LockSurface(surface)) {
    DE_Logger::error("Could not lock SDL surface");
    SDL_DestroySurface(surface);
    stbi_image_free(data);
    return nullptr;
  }

  auto *dst = static_cast<unsigned char *>(surface->pixels);
  for (int row = 0; row < height; ++row) {
    std::memcpy(dst + row * surface->pitch, data + row * src_pitch,
                src_pitch);
  }

  if (must_lock) {
    SDL_UnlockSurface(surface);
  }

  stbi_image_free(data);
  return surface;
}
