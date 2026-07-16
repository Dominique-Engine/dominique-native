# pragma once

typedef struct SDL_Window SDL_Window;
typedef struct SDL_GPUDevice SDL_GPUDevice;
typedef struct SDL_GLContextState *SDL_GLContext;

enum class RendererType {
  SDL_gpu
};

struct DEConfig {
  float clearColor[4];
  const char *title;
  int width;
  int height;
  int flags;
};

struct DE {
  RendererType rendererType = RendererType::SDL_gpu;
  SDL_Window *windowHandler = nullptr;
  SDL_GPUDevice *gpuDevice = nullptr;
  DEConfig config = {0.03f, 0.69f, 0.48f, 0.0f, "DEngine App", 800, 600};
};