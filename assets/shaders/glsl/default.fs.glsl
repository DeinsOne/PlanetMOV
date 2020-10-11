#version 150

uniform sampler2D uTex0;

in vec4		Position;
in vec2		TexCoord;
in vec3		Normal;
in vec4		Color;


out vec4 	oColor;

void main( void )
{
	vec3 normal = normalize( -Normal );
	float diffuse = max( dot( normal, vec3( 0, 0, -1 ) ), 0 );
	oColor = texture( uTex0, TexCoord.st ) * Color * diffuse;
}