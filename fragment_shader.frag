#version 410 core
out vec4 FragColor;

in vec2 xy_pos;
in vec4 rgb_col;

uniform int texture_provided;
uniform sampler2D texture1;

void main()
{
	if (texture_provided == 1)
		FragColor = texture(texture1, xy_pos);
	else
		FragColor = rgb_col;
}
