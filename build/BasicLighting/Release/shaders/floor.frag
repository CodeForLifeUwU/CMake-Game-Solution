#version 330 core

in vec2 gridCoord;

out vec4 FragColor;

uniform vec3 cameraPos;

void main()
{
    // Create checkerboard pattern
    int num1 = int(floor(gridCoord.x));
    int num2 = int(floor(gridCoord.y));

    float dist = distance(cameraPos, vec3(gridCoord.x, 0.0, gridCoord.y));

    float opacity;
    if(dist == 0.0)
        {opacity = 0.5;}
    else {
        opacity = 1/(dist);
        opacity = opacity > 0.5 ? 0.5 : opacity;
    }
    

    vec3 color = (num1+num2)%2==0 ? vec3(1.0) : vec3(0.0);

    FragColor = vec4(color, opacity);
}

