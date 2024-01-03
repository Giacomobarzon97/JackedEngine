#include "DebugCameraActor.h"
#include <iostream>

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
	inputComponent.BindAxis("Move Laterally", std::bind(&DebugCameraActor::MoveLaterally, this, std::placeholders::_1));

	JackedEngine::GetInputManager().CreateAxis("Move Straight");
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Straight", KEY_W, -1.0f);
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Straight", KEY_S, 1.0f);
	inputComponent.BindAxis("Move Straight", std::bind(&DebugCameraActor::MoveStraight, this, std::placeholders::_1));

	JackedEngine::GetInputManager().CreateAxis("Move Vertically");
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Vertically", KEY_Q, -1.0f);
	JackedEngine::GetInputManager().AddMappingToaAxis("Move Vertically", KEY_E, 1.0f);
	inputComponent.BindAxis("Move Vertically", std::bind(&DebugCameraActor::MoveVertically, this, std::placeholders::_1));

	JackedEngine::GetInputManager().CreateAxis("Rotate Horizontally");
	JackedEngine::GetInputManager().AddMappingToaAxis("Rotate Horizontally", MOUSE_X, 1.0f);
	inputComponent.BindAxis("Rotate Horizontally", std::bind(&DebugCameraActor::RotateHorizontally, this, std::placeholders::_1));

	JackedEngine::GetInputManager().CreateAxis("Rotate Vertically");
	JackedEngine::GetInputManager().AddMappingToaAxis("Rotate Vertically", MOUSE_Y, 1.0f);
	//inputComponent.BindAxis("Rotate Vertically", std::bind(&DebugCameraActor::RotateVertically, this, std::placeholders::_1));
}

void DebugCameraActor::Tick(double deltaTime) {
	BaseActor::Tick(deltaTime);
}

void DebugCameraActor::MoveLaterally(float scaleValue) {
	camera.Translate(camera.getYAxis() * movementSpeed * scaleValue);
}

void DebugCameraActor::MoveStraight(float scaleValue) {
	camera.Translate(camera.getXAxis() * movementSpeed * scaleValue * -1.0f);
}

void DebugCameraActor::MoveVertically(float scaleValue) {
	camera.Translate(camera.getZAxis() * movementSpeed * scaleValue * -1.0f);
}

void DebugCameraActor::RotateHorizontally(float scaleValue) {
	camera.Rotate({0, 0, rotationSpeed * scaleValue });
}

void DebugCameraActor::RotateVertically(float scaleValue) {
	float yRotation = rotationSpeed * scaleValue;
	float currentYaw = camera.GetRotation().y;
	if (abs(currentYaw + yRotation) >= maxVerticalRotation) {
		yRotation = ((currentYaw > 0) - (currentYaw < 0)) * maxVerticalRotation - camera.GetRotation().y;
	}
	camera.Rotate({ 0, yRotation, 0 });
}