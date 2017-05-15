#version 430 core

layout (std430, binding = 1 ) buffer shader_data
{
	mat4 ModelMatrix;
    mat4 ViewMatrix;
    mat4 MVP;
    mat4 MV;
    vec4 cameraPos;
    vec4 cameraLook;
    vec4 LightPosition_worldspace[100];
    vec4 LightColor[100];
    vec4 LightDirection[100];
    vec4 external_portals[300];
    vec4 internal_portals[300];
    float LightPower[100];
    float angle[100];
    float ambient_power;
    uint number_of_external_portals;
    uint number_of_internal_portals;
    uint number_of_lights;
    uint textures_enabled; //flag
    uint source_type[100];
};

uniform sampler2D textureSampler;

in vec3 fragmentColor;
in vec2 UV;
in vec3 Normal;
in vec3 Position_worldspace;
out vec3 color;

vec3 findColor()
{
    vec3 EyeDirection = (cameraPos.xyz- Position_worldspace); // ??????????? ???????
	vec3 MaterialDiffuseColor = vec3(0,0,0);
	if (textures_enabled != 0)
		MaterialDiffuseColor = texture(textureSampler, UV).xyz;
	else
		MaterialDiffuseColor = fragmentColor;
	vec3 MaterialAmbientColor = vec3( ambient_power, ambient_power, ambient_power) * MaterialDiffuseColor; // Glow of the object
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);//reflected light (Glare)

	vec3 MDC = vec3(0.0,0.0,0.0);
	vec3 MSC = vec3(0.0,0.0,0.0);
	vec3 e = normalize(EyeDirection); // vector Direction of sight
	vec3 n = ( Normal ); // �normal vector in world space

	for (int i = 0; i < number_of_lights; i++)
	{
    	vec3 l = ( LightPosition_worldspace[i]).xyz - vec3(Position_worldspace) ; //  �light direction from vertex to light
    	vec3 ref, d;
    	float cosTheta, cosAlpha, dist;
	switch (source_type[i])
		{
		case 1:
			//dot -- scalar product
			dist = length(l);
			cosTheta = clamp( dot( n,l )/length(n)/dist, 0, 1 );	// cos of the angle between normal and direction
			ref = normalize(reflect(-l,n)); //direction of reflection
			cosAlpha = clamp( dot( e,ref ), 0,1 );  // cos of angle between vector Direction of sight and vector of reflection
			MDC += MaterialDiffuseColor *LightColor[i].xyz * LightPower[i]* cosTheta / dist/dist ;
			MSC += MaterialSpecularColor * LightColor[i].xyz * LightPower[i] * pow(cosAlpha,5) / dist/dist;

			break;
		case 0:
		    dist = length(l);
			float cosFI = dot(LightDirection[i].xyz, -l)/dist/length(LightDirection[i].xyz);
			if (cosFI <= (angle[i]))
				break;
			//dot -- scalar product
			cosTheta = clamp( dot( n,l )/length(n)/dist, 0, 1 );	// cos of the angle between normal and direction
			ref = normalize(reflect(-l,n)); //direction of reflection
			cosAlpha = clamp( dot( e,ref ), 0,1 );  // cos of angle between vector Direction of sight and vector of reflection
			vec3 addMDC = MaterialDiffuseColor *LightColor[i].rgb * LightPower[i]* cosTheta /dist/dist*(cosFI- angle[i]) ;
			vec3 addMSC = MaterialSpecularColor * LightColor[i].rgb * LightPower[i] * pow(cosAlpha,5) / dist/dist*(cosFI-angle[i]);
			MDC += addMDC;
            MSC += addMSC;
			break;
		case 2:
			if (dot(LightDirection[i].xyz, -n) < 0)
				break;
			MDC += MaterialDiffuseColor *LightColor[i].rgb * LightPower[i];//
			//MSC += MaterialSpecularColor * LightColor[i].rgb * LightPower[i] * pow(cosAlpha,5);
			break;
		default:
			break;

		}
	}
	return MaterialAmbientColor+ MDC + MSC;
}

bool behindPortal()
{
    for(int i = 0; i <number_of_internal_portals; ++i)
    {
        vec3 A = internal_portals[i*3].xyz;
        vec3 B = internal_portals[i*3 + 1].xyz;
        vec3 C = internal_portals[i*3 + 2].xyz;
        vec3 O = cameraPos.xyz;         //view point
        vec3 T = Position_worldspace;   //current point
        vec4 eq = vec4(cross(B - A, C - A), 0); //portal plane equasion
        eq = vec4(eq.xyz, -dot(eq.xyz, A));
        if(dot(eq.xyz, (T - O)) < 0)
            continue;
        float  f1 = dot(eq, vec4(O, 1)), f2 = dot(eq, vec4(T, 1));
        if((f1 < 0 && f2 < 0) || (f1 > 0 && f2 > 0))
            continue;
        f1 = dot(cross(A - O, B - O), C - O);
        f2 = dot(cross(A - O, B - O), T - O);
        if(!((f1 < 0 && f2 < 0) || (f1 > 0 && f2 > 0)))
             continue;
        f1 = dot(cross(A - O, C - O), B - O);
        f2 = dot(cross(A - O, C - O), T - O);
        if(!((f1 < 0 && f2 < 0) || (f1 > 0 && f2 > 0)))
           continue;
        f1 = dot(cross(B - O, C - O), A - O);
        f2 = dot(cross(B - O, C - O), T - O);
        if(!((f1 < 0 && f2 < 0) || (f1 > 0 && f2 > 0)))
             continue;
        return true;
     }
    return false;
}

bool notViaPortal()
{
    if(number_of_external_portals == 0)
        return false;
    for(int i = 0; i <number_of_external_portals; ++i)
    {
        vec3 A = external_portals[i*3].xyz;
        vec3 B = external_portals[i*3 + 1].xyz;
        vec3 C = external_portals[i*3 + 2].xyz;
        vec3 O = cameraPos.xyz;         //view point
        vec3 T = Position_worldspace;   //current point
        vec4 eq = vec4(cross(B - A, C - A), 0); //portal plane equasion
        eq = vec4(eq.xyz, -dot(eq.xyz, A));
        if(dot(eq.xyz, (T - O)) > 0)
            continue;
        float  f1 = dot(eq, vec4(O, 1)), f2 = dot(eq, vec4(T, 1));
        if((f1 < 0 && f2 < 0) || (f1 > 0 && f2 > 0))
            continue;
        f1 = dot(cross(A - O, B - O), C - O);
        f2 = dot(cross(A - O, B - O), T - O);
        if(!((f1 < 0 && f2 < 0) || (f1 > 0 && f2 > 0)))
             continue;
        f1 = dot(cross(A - O, C - O), B - O);
        f2 = dot(cross(A - O, C - O), T - O);
        if(!((f1 < 0 && f2 < 0) || (f1 > 0 && f2 > 0)))
           continue;
        f1 = dot(cross(B - O, C - O), A - O);
        f2 = dot(cross(B - O, C - O), T - O);
        if(!((f1 < 0 && f2 < 0) || (f1 > 0 && f2 > 0)))
             continue;
        return false;
     }
    return true;
}

void main()
{
    if(behindPortal())
        discard;
    if(notViaPortal())
        discard;
    else
	    color = findColor();
}