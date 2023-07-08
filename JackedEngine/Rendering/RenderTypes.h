#include <glm/glm.hpp>

enum ShaderType {
	OBJECT3D,
	SKYBOX
};

struct MeshUniformData {
	glm::mat4 modelMatrix;
};

struct FrameData {
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};