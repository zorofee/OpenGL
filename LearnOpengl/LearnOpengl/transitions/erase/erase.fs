#version 330 core

#define type 8

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float progress;

void main()
{
#if type==1
//划出
	if(TexCoord.x > progress)
	{
		FragColor = texture(texture1,TexCoord);
	}
	else
	{
		FragColor = texture(texture2,TexCoord);
	}

#elif type==2
//滑动
	if(TexCoord.x > progress)
	{
		FragColor = texture(texture1,vec2(TexCoord.x,TexCoord.y));
	}
	else
	{
		FragColor = texture(texture2,vec2(TexCoord.x-progress,TexCoord.y));
	}

#elif type==3
//推动
	if(TexCoord.x > progress)
	{
		FragColor = texture(texture1,vec2(TexCoord.x-progress,TexCoord.y));
	}
	else
	{
		FragColor = texture(texture2,vec2(TexCoord.x-progress,TexCoord.y));
	}

#elif type==4
//时钟smooth
	float smoothness = 1.0;
	float PI = 3.141592653589;
	vec2 rp = TexCoord * 2.0f - 1.0f;
	FragColor = mix(
				texture(texture2,TexCoord),
				texture(texture1,TexCoord),
				smoothstep(0., smoothness, atan(rp.y,rp.x) - (progress-.5) * PI * 2.5)
				);

#elif type==5
//时钟
	float startingAngle = 0;
	float PI = 3.141592653589;
	float offset = startingAngle * PI / 180.0;
	float angle = atan(TexCoord.y - 0.5, TexCoord.x - 0.5) + offset;
	float normalizedAngle = (angle + PI) / (2.0 * PI);
  
	normalizedAngle = normalizedAngle - floor(normalizedAngle);

	FragColor = mix(
				texture(texture1,TexCoord),
				texture(texture2,TexCoord),
				step(normalizedAngle, progress)
				);


#elif type==6
//黑色胶圈
	vec4 bgcolor = vec4(0.0,0.0,0.0,1.0);
	vec2 ratio2 = vec2(1.0,1.0);
	float s = pow(2.0 * abs(progress - 0.5), 3.0);

	float dist = length((vec2(TexCoord) - 0.5) * ratio2);
    FragColor = mix(
				progress < 0.5 ? texture(texture1,TexCoord) : texture(texture2,TexCoord), // branching is ok here as we statically depend on progress uniform (branching won't change over pixels)
				bgcolor,
				step(s, dist)
				);

#elif type==7
//圈入
	float smoothness = 0.3;
	bool opening = true;

	const vec2 center = vec2(0.5, 0.5);
	const float SQRT_2 = 1.414213562373;

	float x = opening ? progress : 1.-progress;
	float m = smoothstep(-smoothness, 0.0, SQRT_2*distance(center, TexCoord) - x*(1.+smoothness));
	FragColor = mix(texture(texture1,TexCoord), texture(texture2,TexCoord), opening ? 1.-m : m);


#elif type==8
	const float SQRT_2 = 1.414213562373;
	float dots = 20.0;
	vec2 center = vec2(0, 0);

	bool nextImage = distance(fract(TexCoord * dots), vec2(0.5, 0.5)) < ( progress / distance(TexCoord, center));
    FragColor = nextImage ? texture(texture2,TexCoord) : texture(texture1,TexCoord);




#endif


}
