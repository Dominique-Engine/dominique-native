#include "core.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <logger/logger.h>
#include <expected>
#include <dengine/utils/fileLoader.h>

#include <format>
#include <iostream>
#include <string>
#include <string_view>


int DE_SdlGpuInit(DE &engine) {
  // initialize SDL
  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK |
                SDL_INIT_HAPTIC | SDL_INIT_GAMEPAD | SDL_INIT_EVENTS |
                SDL_INIT_SENSOR | SDL_INIT_CAMERA)) {
    DE_Logger::error(std::format("Couldn't initialize SDL: {}", SDL_GetError()));
    return 1;
  }

  // if succeeded create our window
  engine.windowHandler = SDL_CreateWindow(
    engine.config.title,
    engine.config.width,
    engine.config.height,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
  // WARN: SDL_WINDOWPOS_CENTERED in macos makes windows to try to be
  // tooltip..ish

  if (engine.windowHandler == nullptr) {
    DE_Logger::error(std::format("Couldn't set video mode: {}", SDL_GetError()));
    return 1;
  }

  SDL_SetLogPriority(SDL_LOG_CATEGORY_GPU, SDL_LOG_PRIORITY_VERBOSE);
  // SDL_Log("SDL version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
  // if the window creation succeeded create our renderer
  engine.gpuDevice = SDL_CreateGPUDevice(
    SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXBC | SDL_GPU_SHADERFORMAT_MSL,
    false,
    nullptr);

  if (engine.gpuDevice == nullptr) {
    DE_Logger::error(std::format("Couldn't create GPU device: {}", SDL_GetError()));
    return 1;
  }

  SDL_ClaimWindowForGPUDevice(engine.gpuDevice, engine.windowHandler);
  return 0;
}

void DE_SdlGpuRender(DE &engine,
                     const DE_Scene *scene,
                     const DE_RenderTarget *target) {
  // TODO
  SDL_GPUCommandBuffer *cmdbuf = SDL_AcquireGPUCommandBuffer(engine.gpuDevice);
  if (cmdbuf == nullptr) {
    DE_Logger::error(std::format("AcquireGPUCommandBuffer failed: %s", SDL_GetError()));
    return;
  }

  SDL_GPUTexture *swapchainTexture;
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdbuf, engine.windowHandler, &swapchainTexture, nullptr, nullptr)) {
    DE_Logger::error(std::format("WaitAndAcquireGPUSwapchainTexture failed: %s", SDL_GetError()));
    return;
  }

  if (swapchainTexture == nullptr) return;

  SDL_GPUColorTargetInfo colorTargetInfo = {0};
  colorTargetInfo.texture = swapchainTexture;
  colorTargetInfo.clear_color = (SDL_FColor){0.3f, 0.4f, 0.5f, 1.0f};
  colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
  colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

  SDL_GPURenderPass *renderPass = SDL_BeginGPURenderPass(cmdbuf, &colorTargetInfo, 1, nullptr);
  SDL_EndGPURenderPass(renderPass);

  SDL_SubmitGPUCommandBuffer(cmdbuf);
}

int DE_SdlGpuClean(DE &engine) {
  DE_Logger::info("Cleaning engine");

  SDL_DestroyGPUDevice(engine.gpuDevice);
  SDL_DestroyWindow(engine.windowHandler);
  SDL_Quit();

  return 0;
}
