#include <glad/glad.h>
#include <iostream>
#include <dengine/spdlog_helper.h>
#include "renderer.h"
#include <stb/stb_image.h>
#include <string>
#include <map>

std::map<de::core::FilterType, int> filterTypeToGLFilter{
    {de::core::FilterType::Lineal, GL_LINEAR},
    {de::core::FilterType::Point, GL_NEAREST}};

void de::core::DrawPrimitive(RenderDataGL &data, RenderTargetGL &target) {
  glUseProgram(data.shader.shaderProgram);
  glBindVertexArray(data.vaoID);

  for (int i = 0; i < data.textures.size(); ++i) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, data.textures[i]);
    SetShaderUniformInt(&data.shader, "texture" + std::to_string(i), i);
  }
  unsigned int transformLoc =
      glGetUniformLocation(data.shader.shaderProgram, "transform");
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(data.trans));

  // Camera related logic
  unsigned int viewLoc =
      glGetUniformLocation(data.shader.shaderProgram, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(target.view));
  unsigned int modelLoc =
      glGetUniformLocation(data.shader.shaderProgram, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(target.model));
  unsigned int projLoc =
      glGetUniformLocation(data.shader.shaderProgram, "projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(target.projection));

  glDrawElements(GL_TRIANGLES, data.vertexNumber, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);  // Unbind our Vertex Array Object
}

void de::core::FillGeometryBuffers(std::vector<float> &vertices,
                                   std::vector<unsigned int> &indices,
                                   DEuint &vaoID, DEuint &vboID,
                                   DEuint &eboID) {
  glGenVertexArrays(1, &vaoID);  // Create our Vertex Array Object
  glBindVertexArray(vaoID);  // Bind our Vertex Array Object so we can use it
  // Vertex buffer object
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
               vertices.data(), GL_STATIC_DRAW);

  // Element buffer object
  glGenBuffers(1, &eboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
               indices.data(), GL_STATIC_DRAW);

  // tell OpenGL how it should interpret the vertex data
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);  // Disable our Vertex Buffer Object
}

void de::core::CreateShader(Shader *shader, const char *vertexShaderSource,
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

void de::core::SetShaderUniformBool(Shader *shader, const std::string &name,
                                    bool value) {
  glUniform1i(glGetUniformLocation(shader->shaderProgram, name.c_str()), value);
}
void de::core::SetShaderUniformInt(Shader *shader, const std::string &name,
                                   int value) {
  glUniform1i(glGetUniformLocation(shader->shaderProgram, name.c_str()), value);
}
void de::core::SetShaderUniformFloat(Shader *shader, const std::string &name,
                                     float value) {
  glUniform1f(glGetUniformLocation(shader->shaderProgram, name.c_str()), value);
}

void de::core::LoadTexture(std::string path, DEuint &textureId,
                           FilterType filterType) {
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *texdata =
      stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, width,
               height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE,
               texdata);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Check if this can be done here
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  filterTypeToGLFilter[filterType]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  filterTypeToGLFilter[filterType]);

  // Check if this can be done here
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  // If set to clamp to border
  //   float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
  // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  stbi_image_free(texdata);
}