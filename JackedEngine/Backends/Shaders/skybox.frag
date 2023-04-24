#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(set = 1, binding = 0) uniform samplerCube samplerCubeMap;

layout(location = 0) in vec3 fragTexCoord;

layout (location = 0) out vec4 outColor;

void main() {
	outColor = texture(samplerCubeMap, fragTexCoord);
}