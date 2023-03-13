#version 450

layout(set = 0, binding = 0) uniform FrameBufferUniform {
    mat4 projectViewMatrix;
} frameUniform;

layout(set = 1, binding = 0) uniform ObjectBufferUniform {
    mat4 modelMatrix;
} objectUniform;


layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

void main() {
    gl_Position =  frameUniform.projectViewMatrix * objectUniform.modelMatrix * inPosition;
    fragTexCoord = inTexCoord;
}