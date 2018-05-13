#version 150 core

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 fragColour;

void main(void)	{	
    // Make blocks a specific colour.
	fragColour = vec4(1,0,0,1);
}