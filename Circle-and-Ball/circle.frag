#version 330 core

out vec4 fragColor;

uniform vec4 uColor = vec4(0.0, 0.0, 0.0, 0.0);

void main()
{
	fragColor = uColor;
}