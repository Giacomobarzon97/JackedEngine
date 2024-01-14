#include "PlaneActor.h"


PlaneActor::PlaneActor(ActorInitializer initializer) :
	BaseActor(initializer),
	meshMaterial("PlaneTexture","../Assets/Textures/earth.jpg"),
	plane(CreateComponent<QuadMeshComponent>("Plane"))
{

	plane.SetMaterial(meshMaterial);
	plane.Translate({ 0,-1.5,0 });
	//plane.Scale({ 1, 0 , 1 });
}

void PlaneActor::Tick(double deltaTime) {
	BaseActor::Tick(deltaTime);
}