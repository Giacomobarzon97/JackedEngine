#pragma once
#include "Scene/Actors/BaseActor.h"
#include "Scene/Components/SkyboxComponent.h"

class SkyboxActor : public BaseActor{
public:
	SkyboxActor(ActorInitializer initializer);

private:
	CubemapMaterial skyboxMaterial;
	SkyboxComponent& skybox;
};