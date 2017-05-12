#version 430
uniform sampler2D textureSampler;
uniform float StepX;
uniform float StepY;

out vec4 color;
in vec2 uv;
in vec2 colorV;
float[5][5] GaussCf =float[5][5]( float[5](0.0029150244650281935, 0.013064233284684921, 0.021539279301848634, 0.013064233284684921 , 0.0029150244650281935 ),
						float[5](0.013064233284684921, 0.05854983152431917  , 0.09653235263005391, 0.05854983152431917 , 0.013064233284684921 ),
						float[5](0.021539279301848634, 0.09653235263005391 , 0.15915494309189535 , 0.09653235263005391 , 0.021539279301848634 ),
							float[5](0.013064233284684921, 0.05854983152431917  , 0.09653235263005391, 0.05854983152431917 , 0.013064233284684921 ),
						float[5](0.0029150244650281935, 0.013064233284684921, 0.021539279301848634, 0.013064233284684921 , 0.0029150244650281935 ));

void main()
{
   vec3 sum = vec3(0,0,0);
   for (int i = -2;i < 3; i++)
   {
	   for (int j = -2; j<3 ; j++)
	   {
			sum+=GaussCf[i+2][j+2]*texture(textureSampler,uv+vec2(i*StepX,j*StepY)).xyz;
	   }
   }
   color = vec4(sum,0.1);
}
