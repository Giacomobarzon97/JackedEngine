#include "VikingRoomActor.h"


VikingRoomActor::VikingRoomActor(ActorInitializer initializer) : 
	BaseActor(initializer),
	meshMaterial("VKingRoomTexture","../Assets/Textures/viking_room.png"),
	vkingRoom(CreateComponent<StaticMeshComponent>("Viking Room"))
{

	vkingRoom.SetModelPath("../Assets/Models/monkey.obj");
	vkingRoom.SetMaterial(meshMaterial);
	vkingRoom.SetPosition({ 0, 0, 0 });
	vkingRoom.Rotate({ 90, 0, -90 });
}

void VikingRoomActor::Tick(double deltaTime) {
	BaseActor::Tick(deltaTime);
	vkingRoom.Rotate({ 0, 0, 10 * deltaTime });
}