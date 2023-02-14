// #include "coreGL.h"
#include "renderer/renderer.h"
#include "shaders.h"

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <dengine/spdlog_helper.h>

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
  auto logger = getMultiSinkLogger();
  // TODO: use a switch to message type, error, warn, info, based on: type ==
  // GL_DEBUG_TYPE_ERROR
  // TODO: log a huan readable version of type and severity
  logger.error("GL CALLBACK: message = {}", message);
}

int dengine::core::InitGL(DE &engine) {
  auto logger = getMultiSinkLogger();

  // initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    logger.error("Couldn't initialize SDL: {}", SDL_GetError());
    return 1;  // sdl could not initialize
  }
  // clean up SDL
  atexit(SDL_Quit);

  // Request an OpenGL 4.3 context (should be core)
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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
    logger.error("Couldn't set video mode: {}", SDL_GetError());
    return 1;
  }

  // if the window creation succeeded create our renderer
  engine.glContext = SDL_GL_CreateContext(engine.windowHandler);

  // Check OpenGL properties
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    logger.error("Failed to initialize OpenGL context");
    return 1;
  }

  logger.info("OpenGL loaded");
  logger.info("Vendor:   {}, Renderer: {}, Version:  {}",
              glGetString(GL_VENDOR), glGetString(GL_RENDERER),
              glGetString(GL_VERSION));

  // Use v-sync
  SDL_GL_SetSwapInterval(1);

  // Enable debug output
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

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

void dengine::core::RenderGL(
    DE &engine, const std::vector<dengine::core::RenderDataGL> &data) {
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto item : data) {
    DrawPrimitive(item.vaoID, item.vboID, item.shader);
  }

  SDL_GL_SwapWindow(engine.windowHandler);
}

int dengine::core::CleanGL(DE &engine) {
  auto logger = getMultiSinkLogger();

  logger.info("Cleaning engine");

  SDL_GL_DeleteContext(engine.glContext);
  SDL_DestroyWindow(engine.windowHandler);
  SDL_Quit();

  return 0;
}

std::function<void(dengine::DE &)> dengine::core::SetupRendererGL(DE &engine) {
  glClear(GL_COLOR_BUFFER_BIT);

  std::vector<RenderDataGL> data;
  data.resize(1);

  // TESTING
  std::vector<float> vertices = {
      -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
  };

  FillGeometryBuffers(vertices, data[0].vaoID, data[0].vboID);

  CreateShader(&data[0].shader, vertexShaderSource, fragmentShaderSource);

  auto renderer = [=](dengine::DE &engine) {
    return dengine::core::RenderGL(engine, data);
  };
  return renderer;
}