#version 450

layout(set = 0, binding = 0) uniform FrameBufferUniform {
    mat4 viewMatrix;
    mat4 projectionMatrix;
} frameUniform;

layout(push_constant) uniform constants {
    mat4 modelMatrix;
} pushConstants;

layout(location = 0) in vec4 inPosition;

layout(location = 0) out vec3 fragTexCoord;

void main() {
    gl_Position = frameUniform.projectionMatrix * mat4(mat3(frameUniform.viewMatrix)) * inPosition;
    fragTexCoord = vec3(inPosition.xy, -inPosition.z);
}