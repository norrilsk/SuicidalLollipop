#version 430

layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;

in VertexData
{
    flat vec3 Position_worldspace;
    vec3 Normal;
    vec3 fragmentColor;
    vec2 UV;
} VertexIn[3];

out vec3 Position_worldspace;
out vec3 Normal;
out vec3 fragmentColor;
out vec2 UV;

 void main()
{
  for(int i = 0; i < gl_in.length(); i++)
  {
     // copy attributes
    gl_Position = gl_in[i].gl_Position;
    Position_worldspace = VertexIn[i].Position_worldspace ;
    Normal = VertexIn[i].Normal;
    UV = VertexIn[i].UV;
    fragmentColor = VertexIn[i].fragmentColor;
    // done with the vertex
    EmitVertex();
  }
}