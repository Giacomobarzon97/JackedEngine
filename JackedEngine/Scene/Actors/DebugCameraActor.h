#pragma once
#include "Scene/Actors/BaseActor.h"
#include "Scene/Components/Cameras/PerspectiveCamera.h"
#include "Scene/Components/InputComponent.h"
#include "JackedEngine.h"

class DebugCameraActor : public BaseActor{
public:
	DebugCameraActor(ActorInitializer initializer);

	virtual void Tick(float deltaTime) override;

	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBack();
	void moveUp();
	void moveDown();

private:
	PerspectiveCamera& camera;
	InputComponent& inputComponent;
	float deltaTime;
	float movementSpeed = 50;
};