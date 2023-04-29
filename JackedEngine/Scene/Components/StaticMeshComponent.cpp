#include "StaticMeshComponent.h"

void StaticMeshComponent::Init() {

}

void StaticMeshComponent::Draw() const {
	if (modelRef.has_value() && material.has_value()) {
		JackedEngine::GetRenderer().Draw(OBJECT3D, modelRef.value(), material.value()->GetDiffuseTexture(), &modelMatrix);
	}
}

void StaticMeshComponent::SetModelPath(const std::string modelPath) {
	CPUGenericMesh mesh(modelPath, true, true);
	modelRef = JackedEngine::GetRenderer().CreateModel(mesh);
}

void StaticMeshComponent::SetMaterial(const GenericMeshMaterial& material) {
	this->material = &material;
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