#include "JackedEngine.h"
#include "Scene\Components\StaticMeshComponent.h"
#include "Scene\Components\SkyboxComponent.h"

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

	std::vector<RenderableComponent*> objects;
	objects.push_back(new StaticMeshComponent(
		"Viking Room",
		"../Assets/Models/viking_room.obj",
		meshMaterial
	));
	
	objects.push_back(new SkyboxComponent(
		"Skybox",
		skyboxMaterial
	));
	
	JackedEngine::MainLoop(objects);

	for (RenderableComponent* component : objects) {
		delete component;
	}
}
