#version 450

layout(set = 0, binding = 0) uniform FrameBufferUniform {
    mat4 viewMatrix;
    mat4 projectionMatrix;
    uint nLights;
} frameUniform;
layout(set = 1, binding = 0) uniform ObjectDataUniform {
    mat4 modelMatrix;
} objectData;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;

void main() {
    gl_Position =  frameUniform.projectionMatrix * frameUniform.viewMatrix * objectData.modelMatrix * vec4(inPosition,1);
    fragTexCoord = inTexCoord;
}