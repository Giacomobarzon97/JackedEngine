#include "DebugCameraActor.h"


DebugCameraActor::DebugCameraActor(ActorInitializer initializer) :
	BaseActor(initializer),
	camera(CreateComponent<PerspectiveCamera>("Camera"))
{
	JackedEngine::SetActiveCamera(camera);
	camera.Translate(2, 0, 0);
}

void DebugCameraActor::Tick(float deltaTime) {
	BaseActor::Tick(deltaTime);
}