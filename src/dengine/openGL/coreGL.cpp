// #include "coreGL.h"
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <dengine/spdlog_helper.h>
#include <dengine/utils/fileLoader.h>

#include <format>
#include <iostream>
#include <string>
#include <string_view>

#include "renderer/renderer.h"

using namespace de::components;
using namespace de::utils::logger;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, DEuint id,
                                GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam) {
  // TODO: use a switch to message type, error, warn, info, based on: type ==
  // GL_DEBUG_TYPE_ERROR
  // TODO: log a huan readable version of type and severity
  Logger::error(std::format("GL CALLBACK: message = {}", message));
}

int de::core::InitGL(DE& engine) {
  // initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    Logger::error(std::format("Couldn't initialize SDL: {}", SDL_GetError()));
    return 1; // sdl could not initialize
  }
  // clean up SDL
  atexit(SDL_Quit);

  // Request an OpenGL 4.3 context (should be core)
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Also request a depth buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // if succeeded create our window
  engine.windowHandler = SDL_CreateWindow(
      engine.config.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      engine.config.width, engine.config.height,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
      SDL_WINDOW_ALLOW_HIGHDPI);

  if (engine.windowHandler == NULL) {
    Logger::error(std::format("Couldn't set video mode: {}", SDL_GetError()));
    return 1;
  }

  SDL_GL_MakeCurrent(engine.windowHandler, engine.glContext);

  // if the window creation succeeded create our renderer
  engine.glContext = SDL_GL_CreateContext(engine.windowHandler);
  if (!engine.glContext) {
    Logger::error(std::format("Failed to initialize OpenGL context: {}",
                              SDL_GetError()));
    return 1;
  }

  // Check OpenGL properties
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    Logger::error("Failed to initialize OpenGL context");
    return 1;
  }

  const GLubyte* glVendor = glGetString(GL_VENDOR);
  const GLubyte* glRenderer = glGetString(GL_RENDERER);
  const GLubyte* glVersion = glGetString(GL_VERSION);
  // Use reinterpret_cast:
  const char* vendorCharPtr = reinterpret_cast<const char*>(glVendor);
  const char* rendererCharPtr = reinterpret_cast<const char*>(glRenderer);
  const char* versionCharPtr = reinterpret_cast<const char*>(glVersion);

  Logger::info("OpenGL loaded");
  Logger::info(std::format("Vendor:   {}, Renderer: {}, Version:  {}",
                           vendorCharPtr, rendererCharPtr,
                           versionCharPtr));

  // Use v-sync
  SDL_GL_SetSwapInterval(1);

  auto ver = glGetString(GL_VERSION);
  if (!ver) {
    std::cerr <<
        "glGetString(GL_VERSION) returned NULL. Context might be invalid.\n";
  } else {
    std::cout << "GL_VERSION: " << reinterpret_cast<const char*>(ver) << "\n";
  }

  glEnable(GL_DEBUG_OUTPUT);

  // Check if the KHR_debug extension is supported
  bool hasKHRDebug = false;
  GLint numExtensions = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
  for (GLint i = 0; i < numExtensions; ++i) {
    const char* ext = reinterpret_cast<const char*>(glGetStringi(
        GL_EXTENSIONS, i));
    if (std::strcmp(ext, "GL_KHR_debug") == 0) {
      hasKHRDebug = true;
      break;
    }
  }

  if (!hasKHRDebug) {
    Logger::warn("GL_KHR_debug not supported on this driver");
  } else {
    // Enable debug output
    glDebugMessageCallback(MessageCallback, nullptr);
  }

  // Disable depth test and face culling.
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  int w, h;
  SDL_GetWindowSize(engine.windowHandler, &w, &h);
  glViewport(0, 0, w, h);

  // base clear color
  glClearColor(engine.config.clearColor[0], engine.config.clearColor[1],
               engine.config.clearColor[2], engine.config.clearColor[3]);

  return 0;
}

void de::core::RenderGL(DE& engine, de::ecs::Scene& scene,
                        de::core::RenderTargetGL& target,
                        const std::vector<de::core::RenderDataGL>& data) {
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto item : data) {
    item.trans = glm::translate(item.trans, glm::vec3(0.5f, -0.5f, 0.0f));
    item.trans = glm::rotate(item.trans, (float)SDL_GetTicks() / 1000,
                             glm::vec3(0.0f, 0.0f, 1.0f));

    DrawPrimitive(item, target);
  }
  SDL_GL_SwapWindow(engine.windowHandler);
}

int de::core::CleanGL(DE& engine) {
  // getMultiSinkLogger().info("Cleaning engine");

  SDL_GL_DeleteContext(engine.glContext);
  SDL_DestroyWindow(engine.windowHandler);
  SDL_Quit();

  return 0;
}

std::function<void(de::DE&, de::ecs::Scene&, de::core::RenderTargetGL&)>
de::core::SetupRendererGL(DE& engine, de::ecs::Scene& scene) {
  glClear(GL_COLOR_BUFFER_BIT);

  std::vector<RenderDataGL> data;
  data.resize(1);

  // TESTING
  std::vector<float> vertices = {
      // positions
      // colors
      // texture coords
      0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 1.0f, // top right
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
      0.0f, 0.0f, 1.0f
      // top left
  };
  std::vector<unsigned int> indices = {
      // note that we start from 0!
      0, 1,
      2, // first triangle
      2, 3,
      0
      // second triangle
  };

  data[0].vertexNumber = indices.size();
  data[0].textures.resize(3);
  FillGeometryBuffers(vertices, indices, data[0].vaoID, data[0].vboID,
                      data[0].eboID);

  LoadTexture("icon.png", data[0].textures[0]);
  LoadTexture("lava.png", data[0].textures[1]);

  data[0].trans =
      glm::rotate(data[0].trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
  data[0].trans = glm::scale(data[0].trans, glm::vec3(0.5, 0.5, 0.5));

  std::string vertexShaderSource;
  std::string fragmentShaderSource;
  de::utils::LoadFileToString("baseFragment.glsl", fragmentShaderSource);
  de::utils::LoadFileToString("baseVertex.glsl", vertexShaderSource);
  CreateShader(&data[0].shader, vertexShaderSource.c_str(),
               fragmentShaderSource.c_str());

  // Wireframe
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // auto renderer = [data](de::DE &engine) {
  //   return de::core::RenderGL(engine, data);
  // };
  auto renderer = [data](de::DE& engine, de::ecs::Scene& scene,
                         de::core::RenderTargetGL& target) {
    return de::core::RenderGL(engine, scene, target, data);
  };
  return renderer;
}