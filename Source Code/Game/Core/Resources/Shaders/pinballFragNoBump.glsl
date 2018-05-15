#version 150 core

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 fragColour;

void main(void)	{	
	fragColour = vec4(0.4,0.4,0.4,1);
}