#version 150 core

uniform float elapsedTime;
uniform float deltaTime;

in vec4		Position;
in vec3		Normal;

out vec4 	oColor;


void main(void )
{
    oColor = vec4(vec3(1.0, 0.9, 0.26 ), 1 );
}
