#include "core.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <dengine/spdlog_helper.h>
#include <dengine/utils/fileLoader.h>

#include <format>
#include <iostream>
#include <string>
#include <string_view>

// #include "renderer/renderer.h"

using namespace de::components;
using namespace de::utils::logger;

int de::core::sdl_gpu::Init(DE &engine) {
  // initialize SDL
  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK |
                SDL_INIT_HAPTIC | SDL_INIT_GAMEPAD | SDL_INIT_EVENTS |
                SDL_INIT_SENSOR | SDL_INIT_CAMERA)) {
    Logger::error(std::format("Couldn't initialize SDL: {}", SDL_GetError()));
    return 1;
  }
  // clean up SDL
  atexit(SDL_Quit);

  // if succeeded create our window
  engine.windowHandler = SDL_CreateWindow(
    engine.config.title,
    engine.config.width,
    engine.config.height,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
  // WARN: SDL_WINDOWPOS_CENTERED in macos makes windows to try to be
  // tooltip..ish

  if (engine.windowHandler == NULL) {
    Logger::error(std::format("Couldn't set video mode: {}", SDL_GetError()));
    return 1;
  }

  SDL_SetLogPriority(SDL_LOG_CATEGORY_GPU, SDL_LOG_PRIORITY_VERBOSE);
  // SDL_Log("SDL version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
  // if the window creation succeeded create our renderer
  engine.gpuDevice = SDL_CreateGPUDevice(
    SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXBC | SDL_GPU_SHADERFORMAT_MSL,
    false,
    nullptr);

  if (engine.gpuDevice == NULL) {
    Logger::error(std::format("Couldn't create GPU device: {}", SDL_GetError()));
    return 1;
  }

  SDL_ClaimWindowForGPUDevice(engine.gpuDevice, engine.windowHandler);
  return 0;
}

void de::core::sdl_gpu::Render(DE &engine,
                               de::ecs::Scene &scene,
                               de::core::RenderTarget &target,
                               const std::vector<de::core::RenderData> &data) {
  // TODO
  SDL_GPUCommandBuffer *cmdbuf = SDL_AcquireGPUCommandBuffer(engine.gpuDevice);
  if (cmdbuf == NULL) {
    SDL_Log("AcquireGPUCommandBuffer failed: %s", SDL_GetError());
  }

  SDL_GPUTexture *swapchainTexture;
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdbuf, engine.windowHandler, &swapchainTexture, NULL, NULL)) {
    SDL_Log("WaitAndAcquireGPUSwapchainTexture failed: %s", SDL_GetError());
  }

  if (swapchainTexture != NULL) {
    SDL_GPUColorTargetInfo colorTargetInfo = {0};
    colorTargetInfo.texture = swapchainTexture;
    colorTargetInfo.clear_color = (SDL_FColor){0.3f, 0.4f, 0.5f, 1.0f};
    colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
    colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

    SDL_GPURenderPass *renderPass = SDL_BeginGPURenderPass(cmdbuf, &colorTargetInfo, 1, NULL);
    SDL_EndGPURenderPass(renderPass);
  }

  SDL_SubmitGPUCommandBuffer(cmdbuf);
}

int de::core::sdl_gpu::Clean(DE &engine) {
  Logger::info("Cleaning engine");

  // TODO Destroy
  SDL_DestroyWindow(engine.windowHandler);
  SDL_Quit();

  return 0;
}

std::function<void(de::DE &, de::ecs::Scene &, de::core::RenderTarget &)>
de::core::sdl_gpu::SetupRenderer(DE &engine, de::ecs::Scene &scene) {
  // TODO
  std::vector<RenderData> data;

  auto renderer = [data](de::DE &engine,
                         de::ecs::Scene &scene,
                         de::core::RenderTarget &target) {
    return de::core::sdl_gpu::Render(engine, scene, target, data);
  };
  return renderer;
}
