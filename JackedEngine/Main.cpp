#include "JackedEngine.h"
#include "Scene\Components\StaticMeshComponent.h"
#include "Scene\Components\SkyboxComponent.h"
#include "Scene\Components\Cameras\PerspectiveCamera.h"

int main() {
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	GenericMeshMaterial meshMaterial("../Assets/Textures/viking_room.png");
	CubemapMaterial skyboxMaterial(
		"../Assets/Textures/Skybox/front.png",
		"../Assets/Textures/Skybox/back.png",
		"../Assets/Textures/Skybox/top.png",
		"../Assets/Textures/Skybox/bottom.png",
		"../Assets/Textures/Skybox/right.png",
		"../Assets/Textures/Skybox/left.png"
	);

	StaticMeshComponent& vkingRoom = JackedEngine::GetWorld().CreateComponent<StaticMeshComponent>();
	vkingRoom.SetModelPath("../Assets/Models/viking_room.obj");
	vkingRoom.SetMaterial(meshMaterial);

	SkyboxComponent& skybox = JackedEngine::GetWorld().CreateComponent<SkyboxComponent>();
	skybox.SetMaterial(skyboxMaterial);

	PerspectiveCamera& camera = JackedEngine::GetWorld().CreateComponent<PerspectiveCamera>();
	JackedEngine::SetActiveCamera(camera);

	JackedEngine::MainLoop();

}
