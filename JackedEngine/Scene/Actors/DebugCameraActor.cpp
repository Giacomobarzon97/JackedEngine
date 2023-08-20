#include "DebugCameraActor.h"

DebugCameraActor::DebugCameraActor(ActorInitializer initializer) :
	BaseActor(initializer),
	camera(CreateComponent<PerspectiveCamera>("Camera")),
	inputComponent(CreateComponent<InputComponent>("InputComponent"))
{
	JackedEngine::SetActiveCamera(camera);
	camera.Translate({ 2, 0, 0 });

	JackedEngine::GetInputManager().CreateAxis("Move Laterally");
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Laterally", KEY_A, 1.0f);
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Laterally", KEY_D, -1.0f);

	JackedEngine::GetInputManager().CreateAxis("Move Straight");
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Straight", KEY_W, -1.0f);
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Straight", KEY_S, 1.0f);

	JackedEngine::GetInputManager().CreateAxis("Move Vertically");
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Vertically", KEY_Q, -1.0f);
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Vertically", KEY_E, 1.0f);

	inputComponent.BindAxis("Move Laterally", std::bind(&DebugCameraActor::MoveLaterally, this, std::placeholders::_1));
	inputComponent.BindAxis("Move Straight", std::bind(&DebugCameraActor::MoveStraight, this, std::placeholders::_1));
	inputComponent.BindAxis("Move Vertically", std::bind(&DebugCameraActor::MoveVertically, this, std::placeholders::_1));
}

void DebugCameraActor::Tick(float deltaTime) {
	BaseActor::Tick(deltaTime);
	this->deltaTime = deltaTime;
}

void DebugCameraActor::MoveLaterally(float scaleValue) {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();	
	glm::vec3 direction{ cameraRotationMatrix[0][2], cameraRotationMatrix[1][2], cameraRotationMatrix[2][2] };
	camera.Translate(direction * movementSpeed * scaleValue);
}

void DebugCameraActor::MoveStraight(float scaleValue) {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();
	glm::vec3 direction{ cameraRotationMatrix[0][0], cameraRotationMatrix[1][0], cameraRotationMatrix[2][0] };
	camera.Translate(direction * movementSpeed * scaleValue);
}

void DebugCameraActor::MoveVertically(float scaleValue) {
	glm::mat4 cameraRotationMatrix = Rotator(camera.GetRotation()).GetRotationMatrix();
	glm::vec3 direction{ cameraRotationMatrix[0][1], cameraRotationMatrix[1][1], cameraRotationMatrix[2][1] };
	camera.Translate(direction * movementSpeed * scaleValue);
}