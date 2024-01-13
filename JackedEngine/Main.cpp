#include "JackedEngine.h"
#include "Scene/Actors/VikingRoomActor.h"
#include "Scene/Actors/SkyboxActor.h"
#include "Scene/Actors/DebugCameraActor.h"
#include "Scene/Actors/RotatingPosLightActor.h"

int main() {
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	JackedEngine::GetWorld().CreateActor<VikingRoomActor>("Viking Room");
	//JackedEngine::GetWorld().CreateActor<SkyboxActor>("Skybox");
	JackedEngine::GetWorld().CreateActor<DebugCameraActor>("Camera");
	JackedEngine::GetWorld().CreateActor<RotatingPosLightActor>("Light");

	JackedEngine::MainLoop();
}
