#pragma once
#include "Scene/Actors/BaseActor.h"
#include "Scene/Components/Cameras/PerspectiveCamera.h"
#include "Scene/Components/InputComponent.h"
#include "JackedEngine.h"

class DebugCameraActor : public BaseActor{
public:
	DebugCameraActor(ActorInitializer initializer);

	virtual void Tick(float deltaTime) override;

	void MoveLaterally(float scaleValue);
	void MoveStraight(float scaleValue);
	void MoveVertically(float scaleValue);
	void RotateHorizontally(float scaleValue);
	void RotateVertically(float scaleValue);

private:
	PerspectiveCamera& camera;
	InputComponent& inputComponent;
	float movementSpeed = 1;
	float rotationSpeed = 100;
	float maxVerticalRotation = 89;
};