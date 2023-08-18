#include "VikingRoomActor.h"


VikingRoomActor::VikingRoomActor(ActorInitializer initializer) : 
	BaseActor(initializer),
	meshMaterial("../Assets/Textures/viking_room.png"),
	vkingRoom(CreateComponent<StaticMeshComponent>("Viking Room"))
{
	vkingRoom.SetModelPath("../Assets/Models/viking_room.obj");
	vkingRoom.SetMaterial(meshMaterial);
	vkingRoom.Rotate(90, 0, -90);
}

void VikingRoomActor::Tick(float deltaTime) {
	BaseActor::Tick(deltaTime);
	vkingRoom.Rotate(0, 0, 10 * deltaTime);
}