#version 330 core

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D cubeTexture;

void main()
{    
    FragColor = texture(cubeTexture, texCoords);
//    FragColor = vec4(1.0, 1.0, 1.0, 1.0); 
}