#version 330 core


out vec2 gridCoord;

uniform vec3 cameraPos;

uniform mat4 view;
uniform mat4 projection;



const vec3 vertices[4] = vec3[4](
	vec3(-1.0, 0.0,  1.0),
	vec3( 1.0, 0.0,  1.0),
	vec3( 1.0, 0.0, -1.0),
	vec3(-1.0, 0.0, -1.0)
);

const int indices[6] = int[6](0, 1, 2, 0, 2, 3);

const float size = 100.0;

void main()
{
	vec3 gridPos = ( (size/2.0)*vertices[indices[gl_VertexID]] ) + ( floor(cameraPos/2.0)*2.0 );
	gridPos.y = 0.0;

	gl_Position = projection * view * vec4(gridPos, 1.0);

	gridCoord = gridPos.xz;
}
