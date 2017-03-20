#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 1, binding = 1) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

/*
layout(push_constant) uniform vertexPushConstants  {
     layout(offset = 0) int instanceJump;
} u_pushConstants;
*/

layout(set = 0, location = 0) in vec3 inPosition;
layout(set = 0, location = 1) in vec2 inTexCoord;
layout(set = 0, location = 2) in vec3 inNormal;
layout(set = 0, location = 3) in vec3 inBinormal;

layout(set = 1, location = 4) in vec4 model1;
layout(set = 1, location = 5) in vec4 model2;
layout(set = 1, location = 6) in vec4 model3;
layout(set = 1, location = 7) in vec4 other;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec4 misc;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    // gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
	
	gl_Position = ubo.proj * ubo.view * vec4(inPosition, 1.0) + model1;
	
    fragTexCoord = inTexCoord;
	misc = other;
}