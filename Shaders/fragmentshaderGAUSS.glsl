#version 430
uniform sampler2D textureSampler;
uniform float Step;
uniform float WtoH;

out vec3 color;
in vec2 uv;
in vec2 colorV;

void main()
{
  /* const float k = 15.0;
   float step = radius / k;
   vec3 res =  vec3(0, 0, 0);
   for(int i = -int(3 * k); i < int(3 * k); ++i)
   {
        for(int j = -int(3 * k); j < int(3 * k); ++j)
        {
            res += exp(-(i * i + j*j)/(2*k*k))*texture(sampler, uv + vec2(i * step* Xcoef, j *step)).rgb;
        }
   }
   res /= 3.14159265 * 2.0 * k* k;*/
   color += texture(textureSampler,uv ).xyz;
   color *= vec3(1, 1, 1);
}
