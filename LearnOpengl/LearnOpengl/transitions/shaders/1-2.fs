#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D mask;

uniform float progress;

uniform float strength = 0.5;

vec4 getFromColor(vec2 _texcoord)
{
    return texture(texture1,_texcoord);
}

vec4 getToColor(vec2 _texcoord)
{
    return texture(texture2,_texcoord);
}

void main () {
    //FragColor = texture(mask,TexCoord);
    //return;
     float displacement = texture(mask, TexCoord).r * strength;

    vec2 uvFrom = vec2(TexCoord.x + progress * displacement, TexCoord.y);
    vec2 uvTo = vec2(TexCoord.x - (1.0 - progress) * displacement, TexCoord.y);

    FragColor = mix(
        getFromColor(uvFrom),
        getToColor(uvTo),
        progress
    );
}
