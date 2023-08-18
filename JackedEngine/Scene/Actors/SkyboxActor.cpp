#include "SkyboxActor.h"


SkyboxActor::SkyboxActor(ActorInitializer initializer) :
	BaseActor(initializer),
	skyboxMaterial(
		"../Assets/Textures/Skybox/front.png",
		"../Assets/Textures/Skybox/back.png",
		"../Assets/Textures/Skybox/top.png",
		"../Assets/Textures/Skybox/bottom.png",
		"../Assets/Textures/Skybox/right.png",
		"../Assets/Textures/Skybox/left.png"
	),
	skybox(CreateComponent<SkyboxComponent>("Skybox"))
{
	skybox.SetMaterial(skyboxMaterial);
}