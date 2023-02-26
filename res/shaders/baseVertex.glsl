#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // color has attribute position 1
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;

out vec4 vertexColor;
out vec2 TexCoord;

void main()
{
  // gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  gl_Position = transform * vec4(aPos, 1.0); // we give a vec3 to vec4’s constructor
  vertexColor = vec4(aColor, 1.0); // output variable to dark-red
  TexCoord = aTexCoord;
}