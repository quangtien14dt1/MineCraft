#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
   FragColor = texture(texture1, texCoord);
}