#version 410 core
layout (location = 0) in vec3 aPos;

out vec2 xy_pos;

uniform mat4 modelmatrix;
// uniform mat4 projectionmatrix;

void main()
{
	// gl_Position = projectionmatrix * modelmatrix * vec4(aPos, 1.0);
	gl_Position = modelmatrix * vec4(aPos, 1.0);
	xy_pos = vec2(aPos.z, aPos.y);
}
