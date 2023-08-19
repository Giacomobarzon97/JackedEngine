#include "DebugCameraActor.h"

DebugCameraActor::DebugCameraActor(ActorInitializer initializer) :
	BaseActor(initializer),
	camera(CreateComponent<PerspectiveCamera>("Camera")),
	inputComponent(CreateComponent<InputComponent>("InputComponent"))
{
	JackedEngine::SetActiveCamera(camera);
	camera.Translate({ 2, 0, 0 });
	inputComponent.BindAction(KEY_W, std::bind(&DebugCameraActor::moveForward, this));
	inputComponent.BindAction(KEY_A, std::bind(&DebugCameraActor::moveLeft, this));
	inputComponent.BindAction(KEY_S, std::bind(&DebugCameraActor::moveBack, this));
	inputComponent.BindAction(KEY_D, std::bind(&DebugCameraActor::moveRight, this));
	inputComponent.BindAction(KEY_Q, std::bind(&DebugCameraActor::moveUp, this));
	inputComponent.BindAction(KEY_E, std::bind(&DebugCameraActor::moveDown, this));
}

void DebugCameraActor::Tick(float deltaTime) {
	BaseActor::Tick(deltaTime);
	this->deltaTime = deltaTime;
}

void DebugCameraActor::moveLeft() {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();	
	glm::vec3 direction{ cameraRotationMatrix[0][2], cameraRotationMatrix[1][2], cameraRotationMatrix[2][2] };
	camera.Translate(direction * deltaTime * movementSpeed);
}

void DebugCameraActor::moveRight() {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();
	glm::vec3 direction{ cameraRotationMatrix[0][2], cameraRotationMatrix[1][2], cameraRotationMatrix[2][2] };
	camera.Translate(direction * deltaTime * -movementSpeed);
}

void DebugCameraActor::moveForward() {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();
	glm::vec3 direction{ cameraRotationMatrix[0][0], cameraRotationMatrix[1][0], cameraRotationMatrix[2][0] };
	camera.Translate(direction * deltaTime * -movementSpeed);
}

void DebugCameraActor::moveBack() {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();
	glm::vec3 direction{ cameraRotationMatrix[0][0], cameraRotationMatrix[1][0], cameraRotationMatrix[2][0] };
	camera.Translate(direction * deltaTime * movementSpeed);
}

void DebugCameraActor::moveUp() {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();
	glm::vec3 direction{ cameraRotationMatrix[0][1], cameraRotationMatrix[1][1], cameraRotationMatrix[2][1] };
	camera.Translate(direction * deltaTime * movementSpeed);
}

void DebugCameraActor::moveDown() {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();
	glm::vec3 direction{ cameraRotationMatrix[0][1], cameraRotationMatrix[1][1], cameraRotationMatrix[2][1] };
	camera.Translate(direction * deltaTime * -movementSpeed);
}