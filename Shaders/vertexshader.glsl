#version 430 core

layout(location = 0) in vec3 vertexPos_modelspace;// ????? VAO
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexNormal_modelspace;
layout (std430, binding = 1) buffer shader_data
{
	mat4 ModelMatrix;
	mat4 ViewMatrix;
	mat4 MVP;
	mat4 MV;
	vec4 cameraPos;
	vec4 LightPosition_worldspace[100];
	vec4 LightColor[100];
	vec4 LightDirection[100];
	float LightPower[100];
	float angle[100];
	float ambient_power;
	uint number_of_lights;
	uint textures_enabled; //flag
	uint source_type[100];
};
// ??????, ?????? ? ????????? ??????
out VertexData
{
   flat vec3 Position_worldspace;
   vec3 Normal;
   vec3 fragmentColor;
   vec2 UV;
};

void main()
{
  gl_Position = MVP* vec4(vertexPos_modelspace, 1); // ??????? ??????? ? ???????? ???????????
  Position_worldspace = (ModelMatrix * vec4(vertexPos_modelspace,1)).xyz; // ??????? ??????? ? ??????? ???????????
  Normal =(ModelMatrix*vec4(vertexNormal_modelspace,0)).xyz; // ?????? ??????? ? ??????? ???????????
  UV = vertexUV;
  fragmentColor = vertexColor;
}