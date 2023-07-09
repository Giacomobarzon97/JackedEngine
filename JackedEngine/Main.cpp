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

	SkyboxComponent& skybox = JackedEngine::GetWorld().CreateComponent<SkyboxComponent>("Skybox");
	skybox.SetMaterial(skyboxMaterial);

	StaticMeshComponent& vkingRoom = JackedEngine::GetWorld().CreateComponent<StaticMeshComponent>("Viking Room");
	vkingRoom.SetModelPath("../Assets/Models/viking_room.obj");
	vkingRoom.SetMaterial(meshMaterial);

	PerspectiveCamera& camera = JackedEngine::GetWorld().CreateComponent<PerspectiveCamera>("Camera");
	JackedEngine::SetActiveCamera(camera);

	vkingRoom.Rotate(90, 0, 90);

	JackedEngine::MainLoop();

}
