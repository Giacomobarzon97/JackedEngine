#include <glm/glm.hpp>

enum ShaderType {
	OBJECT3D,
	SKYBOX
};

struct MeshUniformData {
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
};

struct FrameData {
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};