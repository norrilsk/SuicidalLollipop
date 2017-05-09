#version 430

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

bool OneSidefromPortals()
{
    if(number_of_external_portals == 0)
        return false;
    for(int i = 0; i <number_of_external_portals; ++i)
    {
        vec3 A = external_portals[i*3].xyz;
        vec3 B = external_portals[i*3 + 1].xyz;
        vec3 C = external_portals[i*3 + 2].xyz;
        vec3 O = cameraPos.xyz;         //view point
        vec3 T0 = VertexIn[0].Position_worldspace;   //current point
        vec3 T1 = VertexIn[1].Position_worldspace;   //current point
        vec3 T2 = VertexIn[2].Position_worldspace;   //current point
        vec4 eq = vec4(cross(B - A, C - A), 0); //portal plane equasion
        eq = vec4(eq.xyz, -dot(eq.xyz, A));
        if(dot(eq.xyz, (T0 - O)) < 0 && dot(eq.xyz, (T1 - O)) < 0 && dot(eq.xyz, (T2 - O)) < 0)
            continue;
        float  f1 = dot(eq, vec4(O, 1)), f20 = dot(eq, vec4(T0, 1));
        float  f21 = dot(eq, vec4(T1, 1));
        float  f22 = dot(eq, vec4(T2, 1));

        if((f1 <= 0 && f20 <= 0 && f21 <= 0 && f22 <= 0) || (f1 >= 0 && f20 >= 0 && f21 >= 0 && f22 >= 0))
            continue;
        f1 = dot(cross(A - O, B - O), C - O);
        f20 = dot(cross(A - O, B - O), T0 - O);
        f21 = dot(cross(A - O, B - O), T1 - O);
        f22 = dot(cross(A - O, B - O), T2 - O);
        if(((f1 <= 0 && f20 >= 0 && f21 >= 0 && f22 >= 0) || (f1 >= 0 && f20 <= 0 && f21 <= 0 && f22 <= 0)))
             continue;
        f1 = dot(cross(A - O, C - O), B - O);
        f20 = dot(cross(A - O, C - O), T0 - O);
        f21 = dot(cross(A - O, C - O), T1 - O);
        f22 = dot(cross(A - O, C - O), T2 - O);
        if(((f1 <= 0 && f20 >= 0 && f21 >= 0 && f22 >= 0) || (f1 >= 0 && f20 <= 0 && f21 <= 0 && f22 <= 0)))
           continue;
        f1 = dot(cross(B - O, C - O), A - O);
        f20 = dot(cross(B - O, C - O), T0 - O);
        f21 = dot(cross(B - O, C - O), T1 - O);
        f22 = dot(cross(B - O, C - O), T2 - O);
        if(((f1 <= 0 && f20 >= 0 && f21 >= 0 && f22 >= 0) || (f1 >= 0 && f20 <= 0 && f21 <= 0 && f22 <= 0)))
             continue;
        return false;
     }
    return true;
}

void main()
{
    bool disc = true;//discard triangle if it's behind us;
    for(int i = 0; i < gl_in.length(); i++)
    {
        if(dot(VertexIn[i].Position_worldspace - cameraPos.xyz, cameraLook.xyz) > 0)
        {
            disc = false;
            break;
        }
    }
    if(disc)
        return;
    disc = true;//discard triangle if it's not needed (CULL FACE)
    for(int i = 0; i < gl_in.length(); i++)
    {
        if (dot(VertexIn[i].Position_worldspace - cameraPos.xyz, VertexIn[i].Normal) <= 0)
        {
            disc = false;
            break;
        }
    }
    if(disc)
        return;
    //discard triangle if it's not needed exPortals;
    if (OneSidefromPortals())
    {
         return;
    }
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