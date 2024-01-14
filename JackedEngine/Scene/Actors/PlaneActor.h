#pragma once
#include "Scene/Actors/BaseActor.h"
#include "Scene/Components/QuadMeshComponent.h"

class PlaneActor : public BaseActor{
public:
	PlaneActor(ActorInitializer initializer);
	
	virtual void Tick(double deltaTime) override;

private:
	GenericMeshMaterial meshMaterial;
	QuadMeshComponent& plane;
};