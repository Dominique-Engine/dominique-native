#version 430 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform vec4 ourColor;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
  // FragColor = ourColor;
  // FragColor = vertexColor;
  // FragColor = texture(texture1, TexCoord) * vertexColor;
  FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);
}