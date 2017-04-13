#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 1, binding = 1) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(set = 0, location = 0) in vec3 inPosition;
layout(set = 0, location = 1) in vec2 inTexCoord;
layout(set = 0, location = 2) in vec3 inNormal;
layout(set = 0, location = 3) in vec3 inBinormal;

layout(set = 1, location = 4) in vec4 position;
layout(set = 1, location = 5) in vec4 size;
layout(set = 1, location = 6) in vec4 rotation;
layout(set = 1, location = 7) in vec4 extra;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out float textureIndex;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {

	// Set the texture index
	float texIndex = extra.w;
	
	// Set the initial position
	gl_Position = vec4(inPosition, 1.0);
	
	// Multiply by the size
	gl_Position.x *= size.x;
	gl_Position.y *= size.y;
	
	// Translate
	gl_Position.x += position.x;
	gl_Position.y += position.y;
	
	gl_Position = ubo.proj * gl_Position;
	gl_Position.x -= 1.0;
	gl_Position.y -= 1.0;
	
	// Set the output variables
    fragTexCoord = inTexCoord;
	textureIndex = texIndex;
}