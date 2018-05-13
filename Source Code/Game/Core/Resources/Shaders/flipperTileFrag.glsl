#version 150 core

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 fragColour;

void main(void)	{	
	// Make flippers a specific colour.
	fragColour = vec4(0,0,1,1);
}