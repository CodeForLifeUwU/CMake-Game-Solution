#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

void main()
{
    // Create checkerboard pattern
    int num1 = int(floor(TexCoord.x*10.0));
    int num2 = int(floor(TexCoord.y*10.0));

    FragColor = (num1+num2)%2==0 ? vec4(1.0,1.0,1.0,1.0) : vec4(0.0,0.0,0.0,0.0);
}

