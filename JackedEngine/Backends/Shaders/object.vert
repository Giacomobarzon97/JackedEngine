#version 450

layout(set = 0, binding = 0) uniform FrameBufferUniform {
    mat4 viewMatrix;
    mat4 projectionMatrix;
} frameUniform;

layout(push_constant) uniform constants {
    mat4 modelMatrix;
} pushConstants;

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

void main() {
    gl_Position =  frameUniform.projectionMatrix * frameUniform.viewMatrix * pushConstants.modelMatrix * inPosition;
    fragTexCoord = inTexCoord;
}