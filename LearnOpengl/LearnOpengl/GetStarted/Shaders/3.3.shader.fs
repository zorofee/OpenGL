#version 330 core
#extension GL_EXT_shader_pixel_local_storage : require

out vec4 FragColor;

in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f);
}