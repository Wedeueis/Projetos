#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;
uniform sampler2D tex[32];

in vec4 fposition;
in vec2 fuv;
in float ftid;
in vec4 fcolor;

void main()
{
	float intensity = 1.0 / length(fposition.xy - light_pos);
	vec4 texColor = fcolor;
	if(ftid>0.0){
		int tid = int(ftid - 0.5);
		texColor = fcolor*texture(tex[tid], fuv);
	}
	color = texColor;//*intensity;
}
