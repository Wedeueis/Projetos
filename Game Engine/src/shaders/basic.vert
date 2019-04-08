#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;
uniform mat4 ml_matrix;

out vec4 fposition;
out vec2 fuv;
out float ftid;
out vec4 fcolor;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(position, 1.0);
	fposition = ml_matrix * vec4(position, 1.0);
	fuv = uv;
	ftid = tid;
	fcolor = color;
}