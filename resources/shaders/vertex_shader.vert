#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec2 xy_pos;
out vec4 rgb_col;

uniform mat4 projectionmatrix;
uniform mat4 viewmatrix;
uniform mat4 modelmatrix;

void main()
{
	gl_Position = projectionmatrix * viewmatrix * modelmatrix * vec4(aPos, 1.0);
	xy_pos = vec2(aPos.z, aPos.y);
	rgb_col = vec4(aCol, 1.0f);
}
