#pragma once

#include <dengine/core.h>
#include <vector>
#include <dengine/components/types.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <dengine/scene/scene.h>


struct DE_RenderTarget {
  glm::mat4 model{1.0f};
  glm::mat4 projection{1.0f};
  glm::mat4 view{1.0f};
};

struct DE_Shader {
  DEuint shaderProgram;
  DEuint vertexShader;
  DEuint fragmentShader;
};

struct DE_RenderData {
  DE_Shader shader;
  DEuint vaoID; // Vertex Array Object
  DEuint eboID; // Element Array Object
  DEuint vboID; // Vertex Buffer Object
  std::vector<DEuint> textures;
  int vertexNumber;
  glm::mat4 trans{1.0f};
};

enum class DE_FilterType {
  Lineal,
  Point,
};

int DE_SdlGpuInit(DE &engine);

int DE_SdlGpuClean(DE &engine);

void DE_SdlGpuRender(DE &engine,
            DE_Scene &scene,
            DE_RenderTarget &target);
