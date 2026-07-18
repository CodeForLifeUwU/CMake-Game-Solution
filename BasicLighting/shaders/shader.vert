#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 normal;
out vec3 color;

void main(){
	gl_Position = vec4(aPos.xyz, 1.0);
	normal = aNormal;
	color = aColor;
}
