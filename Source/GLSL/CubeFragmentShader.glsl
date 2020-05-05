#version 410 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D cube_tc;

void main()
{
    FragColor = texture(cube_tc, TexCoords);
}
