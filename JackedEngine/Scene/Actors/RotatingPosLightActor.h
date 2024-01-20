#pragma once
#include <math.h>
#include "Scene/Actors/BaseActor.h"
#include "Scene/Components/Lights/PointLightComponent.h"

class RotatingPosLightActor : public BaseActor{
public:
	RotatingPosLightActor(ActorInitializer initializer);
	
	virtual void Tick(double deltaTime) override;

private:
	float radius = 3;
	float rotationSpeed = 0.5;
	float alpha = 0;
	PointLightComponent& pointLightComponent;
};