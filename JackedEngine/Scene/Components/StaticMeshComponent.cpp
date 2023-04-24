#include "StaticMeshComponent.h"

StaticMeshComponent::StaticMeshComponent(const std::string name, const std::string modelPath, const std::string texturePath) :
	RenderableComponent(name),
	modelPath(modelPath),
	texturePath(texturePath)
{
	CPUImage texture(texturePath, IMAGE_2D);
	CPUGenericMesh mesh(modelPath, true, true);
	textureRef = JackedEngine::Renderer().CreateTexture(texture);
	modelRef = JackedEngine::Renderer().CreateModel(mesh);
}

void StaticMeshComponent::Draw() {
	JackedEngine::Renderer().Draw(OBJECT3D, modelRef, textureRef, &modelMatrix);
}

void StaticMeshComponent::Rotate(const double x, const double y, const double z) {
	if (x != 0) {
		double radAngle = x * M_PI / 180;
		glm::mat4 rotMat = {
			{1,0,0,0},
			{0, cos(radAngle), -sin(radAngle),0},
			{0, sin(radAngle), cos(radAngle),0},
			{0,0,0,1},
		};
		modelMatrix = modelMatrix * rotMat;
	}
	if (y != 0) {
		double radAngle = y * M_PI / 180;
		glm::mat4 rotMat = {
			{cos(radAngle),0,sin(radAngle),0},
			{0, 1, 0,0},
			{-sin(radAngle), 0, cos(radAngle),0},
			{0,0,0,1}
		};
		modelMatrix = modelMatrix * rotMat;
	}
	if (z != 0) {
		double radAngle = z * M_PI / 180;
		glm::mat4 rotMat = {
			{cos(radAngle), -sin(radAngle), 0,0},
			{sin(radAngle), cos(radAngle), 0,0},
			{0, 0, 1,0},
			{0,0,0,1}
		};
		modelMatrix = modelMatrix * rotMat;
	}
}

void StaticMeshComponent::Translate(const double x, const double y, const double z) {

}

void StaticMeshComponent::Scale(const double x, const double y, const double z) {

}

void StaticMeshComponent::SetPosition(const double x, const double y, const double z) {

}

void StaticMeshComponent::SetRotation(const double x, const double y, const double z) {

}

void StaticMeshComponent::SetScale(const double x, const double y, const double z) {

}

const glm::mat4 StaticMeshComponent::GetModelMatrix() const {
	return modelMatrix;
}