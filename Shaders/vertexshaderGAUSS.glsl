#version 430 core
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 vertexUV;

out vec2 uv;
out vec2 colorV;

void main()
{
    uv = vertexUV;
    colorV = vertexPos.xy;
    gl_Position = vec4(vertexPos, 1);
}
