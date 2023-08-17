#version 450

layout(set = 0, binding = 0) uniform FrameBufferUniform {
    mat4 viewMatrix;
    mat4 projectionMatrix;
} frameUniform;

layout(set = 1, binding = 0) uniform ObjectDataUniform {
    mat4 translationMatrix;
    mat4 rotationMatrix;
    mat4 scaleMatrix;
} objectData;

layout(location = 0) in vec4 inPosition;

layout(location = 0) out vec3 fragTexCoord;

void main() {
    gl_Position = (frameUniform.projectionMatrix * mat4(mat3(frameUniform.viewMatrix)) * vec4(inPosition.xyz, 1.0)).xyww;
    fragTexCoord = vec3(inPosition.xy, -inPosition.z);
}