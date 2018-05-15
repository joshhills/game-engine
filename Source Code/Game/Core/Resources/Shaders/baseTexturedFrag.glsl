#version 150 core

uniform sampler2D activeTex;

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;


out vec4 fragColour;

void main(void)	{	
	fragColour = texture(activeTex, IN.texCoord);
}