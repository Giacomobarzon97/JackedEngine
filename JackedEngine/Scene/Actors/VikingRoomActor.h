#pragma once
#include "Scene/Actors/BaseActor.h"
#include "Scene/Components/Renderables/StaticMeshComponent.h"

class VikingRoomActor : public BaseActor{
public:
	VikingRoomActor(ActorInitializer initializer);
	
	virtual void Tick(double deltaTime) override;

private:
	GenericMeshMaterial meshMaterial;
	StaticMeshComponent& vkingRoom;
};