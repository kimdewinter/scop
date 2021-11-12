#version 410 core
layout (location = 0) in vec3 aPos;

out vec2 xy_pos;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	xy_pos = vec2(gl_Position.x, gl_Position.y);
}
