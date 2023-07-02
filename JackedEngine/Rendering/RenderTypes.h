#include <glm/glm.hpp>

enum ShaderType {
	OBJECT3D,
	SKYBOX
};

struct ComponentData {
	glm::mat4 modelMatrix;
};