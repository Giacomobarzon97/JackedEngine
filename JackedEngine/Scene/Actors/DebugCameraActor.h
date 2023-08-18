#pragma once
#include "Scene/Actors/BaseActor.h"
#include "Scene\Components\Cameras\PerspectiveCamera.h"
#include "JackedEngine.h"

class DebugCameraActor : public BaseActor{
public:
	DebugCameraActor(ActorInitializer initializer);

	virtual void Tick(float deltaTime) override;

private:
	PerspectiveCamera& camera;
};