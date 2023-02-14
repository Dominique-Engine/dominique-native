#include <glad/glad.h>
#include <iostream>
#include <dengine/spdlog_helper.h>
#include "renderer.h"

void dengine::core::DrawPrimitive(GLuint vaoID, GLuint vboID, Shader shader) {
  glUseProgram(shader.shaderProgram);
  glBindVertexArray(vaoID);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);  // Unbind our Vertex Array Object
}

void dengine::core::FillGeometryBuffers(std::vector<float> &vertices,
                                        GLuint &vaoID, GLuint &vboID) {
  glGenVertexArrays(1, &vaoID);  // Create our Vertex Array Object
  glBindVertexArray(vaoID);  // Bind our Vertex Array Object so we can use it

  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
               vertices.data(), GL_STATIC_DRAW);

  // tell OpenGL how it should interpret the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);  // Disable our Vertex Array Object
  glBindVertexArray(0);          // Disable our Vertex Buffer Object
}

void dengine::core::CreateShader(Shader *shader, const char *vertexShaderSource,
                                 const char *fragmentShaderSource) {
  // vertex shader
  shader->vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader->vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(shader->vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader->vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader->vertexShader, 512, NULL, infoLog);
    getMultiSinkLogger().error("ERROR::SHADER::VERTEX::COMPILATION_FAILED {}",
                               infoLog);
  }

  // fragment shader
  shader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader->fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(shader->fragmentShader);
  glGetShaderiv(shader->fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader->fragmentShader, 512, NULL, infoLog);
    getMultiSinkLogger().error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED {}",
                               infoLog);
  }

  // shader program
  shader->shaderProgram = glCreateProgram();
  glAttachShader(shader->shaderProgram, shader->vertexShader);
  glAttachShader(shader->shaderProgram, shader->fragmentShader);
  glLinkProgram(shader->shaderProgram);
  glGetProgramiv(shader->shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader->shaderProgram, 512, NULL, infoLog);
    getMultiSinkLogger().error("ERROR::SHADER::VERTEX::COMPILATION_FAILED {}",
                               infoLog);
  }
  glDeleteShader(shader->vertexShader);
  glDeleteShader(shader->fragmentShader);
}