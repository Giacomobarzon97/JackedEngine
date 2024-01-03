#version 450
#extension GL_KHR_vulkan_glsl : enable

struct Light {
    vec4 position;
    vec3 lightColor;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

layout(set = 0, binding = 0) uniform FrameBufferUniform {
    mat4 viewMatrix;
    mat4 projectionMatrix;
    uint nLights;
} frameUniform;
layout(set = 2, binding = 0) uniform sampler2D texSampler;
layout(set = 3, binding = 0) readonly buffer Lights{
	Light lights[];
} lights;
layout(set = 4, binding = 0) uniform MaterialUniform {
    vec3 kAmbient;
	vec3 kDiffuse;
	vec3 kSpecular;
} materialUniform;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;

layout (location = 0) out vec4 outColor;

void main() {
	vec3 totalIntensity = {0,0,0};
	vec4 objectColor = texture(texSampler, inTexCoord);
	vec3 normal = normalize(inNormal);

	for(int i = 0; i < frameUniform.nLights; i++){
		Light light = lights.lights[i];
		vec3 lightDir = normalize(inPosition - light.position.xyz);
		float diffuseRate = max(dot(normal, lightDir), 0.0);

		vec3 ambient = light.lightColor * materialUniform.kAmbient;
		vec3 diffuse = light.lightColor * diffuseRate;
		totalIntensity = totalIntensity + diffuse + ambient;
	}
    
	outColor = vec4((totalIntensity * objectColor.xyz),1);
}