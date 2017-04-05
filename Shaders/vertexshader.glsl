#version 330 core

layout(location = 0) in vec3 vertexPos;// номер VAO
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;

uniform mat4 MVP;

out vec3 fragmentColor;
out vec2 UV;

void main()
{
  UV = vertexUV;
  fragmentColor = vertexColor;
  gl_Position = MVP* vec4(vertexPos, 1);
}
