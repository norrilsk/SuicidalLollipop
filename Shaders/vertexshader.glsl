#version 330 core

layout(location = 0) in vec3 vertexPos; //VAO[0] - координаты вершины
layout(location = 1) in vec3 vertexColor; //VAO[1] - wdtn вершины
uniform mat4 MVP;

out vec3 fragmentColor;

void main()
{
  fragmentColor = vertexColor;
  gl_Position = MVP* vec4(vertexPos, 1);
}