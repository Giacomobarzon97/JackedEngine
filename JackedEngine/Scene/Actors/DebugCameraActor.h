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

private:
	PerspectiveCamera& camera;
	InputComponent& inputComponent;
	float deltaTime;
	float movementSpeed = 1;
};