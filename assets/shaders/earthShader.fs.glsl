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

    vec3 color1 = vec3(0.27059, 0.63922, 0.34902 );
    vec3 color2 = vec3(0.47059, 0.73922, 0.44902 );


    float mixValue = distance(st, vec2(cos(elapsedTime)/2, sin(elapsedTime)/2) );
    vec3 color = mix(color1, color2, mixValue );

    oColor = vec4(color, 1 );
}
