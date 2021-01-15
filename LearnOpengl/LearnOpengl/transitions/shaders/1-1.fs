#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float progress;

vec2 direction = vec2(0.0, 1.0);

vec4 getFromColor(vec2 _texcoord)
{
    return texture(texture1,_texcoord);
}

vec4 getToColor(vec2 _texcoord)
{
    return texture(texture2,_texcoord);
}

void main () {
  vec2 p = TexCoord + progress * sign(direction);
  vec2 f = fract(p);
  FragColor = mix(
    getToColor(f),
    getFromColor(f),
    step(0.0, p.y) * step(p.y, 1.0) * step(0.0, p.x) * step(p.x, 1.0)
  );
}
