#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 0) uniform sampler2DArray texSampler;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec4 misc;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(texSampler, vec3(fragTexCoord, misc.x));
}