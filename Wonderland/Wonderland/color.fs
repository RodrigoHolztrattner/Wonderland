////////////////////////////////////////////////////////////////////////////////
// Filename: color.fs
////////////////////////////////////////////////////////////////////////////////
#version 400

/////////////////////
// INPUT VARIABLES //
/////////////////////
in vec2 texCoordinates;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
out vec4 outputColor;

///////////////////////
// UNIFORM VARIABLES //
///////////////////////
uniform vec4 baseColor;

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	outputColor = baseColor;
}
