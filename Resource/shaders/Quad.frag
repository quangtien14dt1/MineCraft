#version 330 core

out vec4 outColour;

in vec2 texCoords;

uniform sampler2D quadTexture;

void main()
{    
    outColour = texture(quadTexture, texCoords);
}