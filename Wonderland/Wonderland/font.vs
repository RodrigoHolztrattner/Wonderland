////////////////////////////////////////////////////////////////////////////////
// Filename: color.vs
////////////////////////////////////////////////////////////////////////////////
#version 400

/////////////////////
// INPUT VARIABLES //
/////////////////////
in vec3 inputPosition;
in vec2 texCoord;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
out vec2 texCoordinates;

///////////////////////
// UNIFORM VARIABLES //
///////////////////////
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 localMatrix;

uniform vec4 glyphTextureCoord;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	// Set the output vertex position
	gl_Position = vec4(inputPosition, 1.0f);

	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = worldMatrix * gl_Position;
	gl_Position = localMatrix * gl_Position;
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;

	// Store the input color for the pixel shader to use.
	texCoordinates = texCoord;
	
	
	texCoordinates.x = glyphTextureCoord.x + glyphTextureCoord.z * texCoord.x;
	texCoordinates.y = glyphTextureCoord.y + glyphTextureCoord.w * texCoord.y;
}
