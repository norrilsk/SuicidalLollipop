#version 430 core

layout (std430, binding = 1 ) buffer shader_data
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

uniform sampler2D textureSampler;

in vec3 fragmentColor;
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal;
in vec3 EyeDirection; 
in vec3 time;

out vec3 color;


void main()
{
	vec3 MaterialDiffuseColor = vec3(0,0,0);
	if (textures_enabled != 0)
		MaterialDiffuseColor = texture(textureSampler, UV).xyz;
	else
		MaterialDiffuseColor = fragmentColor;
  
	vec3 MaterialAmbientColor = vec3( ambient_power, ambient_power, ambient_power) * MaterialDiffuseColor; // Glow of the object
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);//reflected light (Glare)

	vec3 MDC = vec3(0.0,0.0,0.0);
	vec3 MSC = vec3(0.0,0.0,0.0);
	vec3 e;
	for (int i = 0; i < number_of_lights; i++)
	{
	
	switch (source_type[i])
		{
		case 1:
			vec3 n = ( Normal ); // ­normal vector in world space
			vec3 l = ( LightPosition_worldspace[i]).xyz - Position_worldspace; //  ­light direction from vertex to light
			//dot -- scalar product
			float cosTheta = clamp( dot( n,l )/length(n)/length(l), 0, 1 );	// cos of the angle between normal and direction
			e = normalize(EyeDirection); // vector Direction of sight
			vec3 ref = normalize(reflect(-l,n)); //direction of reflection 
			float cosAlpha = clamp( dot( e,ref ), 0,1 );  // cos of angle between vector Direction of sight and vector of reflection 
			if ((cosAlpha == 0) && (cosTheta == 0))
				break;
			float dist = length( LightPosition_worldspace[i].xyz - Position_worldspace );// distance from vertex to light source
			MDC += MaterialDiffuseColor *LightColor[i].xyz * LightPower[i]* cosTheta / (dist*dist) ;
			MSC += MaterialSpecularColor * LightColor[i].xyz * LightPower[i] * pow(cosAlpha,5) / (dist*dist);
			
			break;
		case 0:
			l = (LightPosition_worldspace[i]).xyz - Position_worldspace; //  ­light direction from light source to vertex
			float cosFI = dot(LightDirection[i].xyz, -l)/length(l)/length(LightDirection[i].xyz);
			if (cosFI <= (angle[i]))
				break;
			n = ( Normal ); // ­normal vector in world space
			//dot -- scalar product
			cosTheta = clamp( dot( n,l )/length(n)/length(l), 0, 1 );	// cos of the angle between normal and direction
			e = normalize(EyeDirection); // vector Direction of sight
			ref = normalize(reflect(-l,n)); //direction of reflection 
			cosAlpha = clamp( dot( e,ref ), 0,1 );  // cos of angle between vector Direction of sight and vector of reflection 
			dist = length( LightPosition_worldspace[i].xyz - Position_worldspace );// distance from vertex to light source
			MDC += MaterialDiffuseColor *LightColor[i].rgb * LightPower[i]* cosTheta /(dist*dist)*(cosFI- angle[i]) ;
			MSC += MaterialSpecularColor * LightColor[i].rgb * LightPower[i] * pow(cosAlpha,5) / (dist*dist)*(cosFI-angle[i]);
			break;
		case 2:

			n = ( Normal ); // ­normal vector in world space
			if (dot(LightDirection[i].xyz, -n) < 0)
				break;
			MDC += MaterialDiffuseColor *LightColor[i].rgb * LightPower[i];//
			MSC += MaterialSpecularColor * LightColor[i].rgb * LightPower[i] * pow(cosAlpha,5);
			break;
		default:
			break;

		} 
	}	
	
	color = MaterialAmbientColor+ MDC + MSC;
}