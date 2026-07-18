#version 330 core

out vec4 FragColor;
//in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D color0;
uniform sampler2D color1;

void main()
{
	FragColor = mix(color(color0, TexCoord), color(color1, TexCoord), 0.2);
	//FragColor = color(ourcolor, TexCoord) * vec4(ourColor, 1.0);
}