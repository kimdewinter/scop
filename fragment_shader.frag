#version 410 core
out vec4 FragColor;

in vec2 xy_pos;

uniform int texture_provided;
uniform sampler2D texture1;

void main()
{
	if (texture_provided == 1)
		FragColor = texture(texture1, xy_pos);
	else
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
