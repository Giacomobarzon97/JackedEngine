#version 450
#extension GL_KHR_vulkan_glsl : enable
#extension GL_EXT_debug_printf : enable

struct Light {
    vec4 position;
    vec4 lightColor;
	float radius;
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
    vec4 kAmbient;
	vec4 kDiffuse;
	vec4 kSpecular;
	uint shinininess;
} materialUniform;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;

layout (location = 0) out vec4 outColor;

void main() {
	vec3 totalIntensity = {0,0,0};
	vec4 objectColor = texture(texSampler, inTexCoord);
	vec3 normal = normalize(inNormal);
	vec3 cameraPosition = inverse(frameUniform.viewMatrix)[3].xyz;
	vec3 viewDir = normalize(cameraPosition - inPosition);

	for(int i = 0; i < frameUniform.nLights; i++){
		Light light = lights.lights[i];
		vec3 lightDir = normalize(inPosition - light.position.xyz);

		vec3 ambient = light.lightColor.xyz * materialUniform.kAmbient.xyz * materialUniform.kAmbient.xyz;

		float diffuseRate = max(dot(normal, lightDir), 0.0);
		vec3 diffuse = light.lightColor.xyz * diffuseRate * materialUniform.kDiffuse.xyz;

		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialUniform.shinininess);
		vec3 specular = materialUniform.kSpecular.xyz * spec * light.lightColor.xyz;

		vec3 currentIntensity = diffuse + ambient + specular;
		float lightDistance = distance(inPosition, light.position.xyz);
		float attenuation = 1 / pow((lightDistance/light.radius)+1,2);
		totalIntensity = totalIntensity + currentIntensity * attenuation;
	}
    
	outColor = vec4((totalIntensity * objectColor.xyz),1);
}