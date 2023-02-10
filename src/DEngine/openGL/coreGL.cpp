#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>

#include "coreGL.h"
#include <DEngine/spdlog_helper.h>
#include "shaders.h"


int DEngine::Core::InitGL(DE &engine)
{
    auto logger = getMultiSinkLogger();

    // initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        // clean up SDL
        atexit (SDL_Quit);

        // Request an OpenGL 4.3 context (should be core)
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        // Also request a depth buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // if succeeded create our window
        engine.windowHandler = SDL_CreateWindow(
            engine.config.title,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            engine.config.width,
            engine.config.height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
        );


        if (engine.windowHandler == NULL)
        {
            logger.error("Couldn't set video mode: {}", SDL_GetError());
            return 1;
        }

        // if the window creation succeeded create our renderer
        engine.glContext = SDL_GL_CreateContext(engine.windowHandler);

    }
    else
    {
        logger.error("Couldn't initialize SDL: {}", SDL_GetError());
        return 1; // sdl could not initialize
    }
 

    // Check OpenGL properties
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress) )
    {
        logger.error( "Failed to initialize OpenGL context" );
        return 1;
    }
    logger.info("OpenGL loaded");
    logger.info("Vendor:   {}, Renderer: {}, Version:  {}", glGetString(GL_VENDOR),glGetString(GL_RENDERER),glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int w,h;
    SDL_GetWindowSize(engine.windowHandler, &w, &h);
    glViewport(0, 0, w, h);
    
    //base clear color
    glClearColor(
        engine.config.clearColor[0],
        engine.config.clearColor[1],
        engine.config.clearColor[2],
        engine.config.clearColor[3]
        );

    return 0;
} 


void DEngine::Core::RenderGL(DE &engine)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // TESTING
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        getMultiSinkLogger().info("ERROR::SHADER::VERTEX::COMPILATION_FAILED {}", infoLog);
    }

    // fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        getMultiSinkLogger().info("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED {}", infoLog);
    }

    // shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        getMultiSinkLogger().info("ERROR::SHADER::VERTEX::COMPILATION_FAILED {}", infoLog);
    }
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //  tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // DONE TESTING

    SDL_GL_SwapWindow(engine.windowHandler);

}

int DEngine::Core::CleanGL(DE &engine)
{
    auto logger = getMultiSinkLogger();

    logger.info("Cleaning engine");

    SDL_GL_DeleteContext(engine.glContext);
    SDL_DestroyWindow(engine.windowHandler);
    SDL_Quit();

    return 0;
}