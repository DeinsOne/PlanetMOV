#version 150 core

uniform float elapsedTime;
uniform float deltaTime;
uniform float planetRadius;

in vec4		Position;
in vec3		Normal;

out vec4 	oColor;


void main(void )
{
    vec2 st = Position.xy/vec2(planetRadius);

    vec3 color1 = vec3(1.0 );
    vec3 color2 = vec3(0.73333, 0.83922, 0.84706 );


    float mixValue = distance(st, vec2(cos(elapsedTime)/2, sin(elapsedTime)/2) );
    vec3 color = mix(color1, color2, mixValue );

    oColor = vec4(color, 1 );
}
 
