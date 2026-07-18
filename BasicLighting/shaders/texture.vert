#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

//out vec3 ourColor;
out vec2 TexCoord;

uniform float rotation;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    
	// Convert rotation to radians
	float rad = rotation * 3.14159265 / 180.0;
	float cosA = cos(rad);
	float sinA = sin(rad);

    //Directed ray
    // r = a + b*t
    
    vec3 a = vec3(0.0f, 0.0f, 0.0f); // Origin of ray

    vec3 b = vec3(0.0f, 1.0f, 0.0f); // Direction of ray
    
    
    vec3 offset = vec3(-0.0, 0.0, 0.0);
        
    vec3 P = aPos + offset;
        
    float t = dot(b, P - a); // Parameter of ray
    // t = (  b•(P - a)  )/(b•b) for c

    vec3 c = a + b*t;
        
    vec3 e1 = P - c;
    vec3 e2 = cross(b, e1);
        
    vec3 Q = e1*cos(rad) + e2*sin(rad);
    Q = Q + c;


	vec3 distortedPos = Q;
	//distortedPos.x += aMode.x * 0.15 * sin(3.14159265*rad);
	//distortedPos.y += aMode.y * 0.15 * sin(2*rad);




	// Rotate position around origin (0, 0)
	vec3 rotatedPos = vec3(
		(distortedPos.x + offset.x) * cosA - (distortedPos.y + offset.y) * sinA,
		(distortedPos.x + offset.x) * sinA + (distortedPos.y + offset.y) * cosA,
		distortedPos.z
	);

    rotatedPos -= offset;
    
	gl_Position = projection * view * model * vec4(rotatedPos, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	//ourColor = aColor;
	TexCoord = aTexCoord;
}