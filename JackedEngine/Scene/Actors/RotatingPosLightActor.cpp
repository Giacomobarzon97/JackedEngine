#include "RotatingPosLightActor.h"


RotatingPosLightActor::RotatingPosLightActor(ActorInitializer initializer) :
	BaseActor(initializer),
	pointLightComponent(CreateComponent<PointLightComponent>("PointLightComponent"))
{
}

void RotatingPosLightActor::Tick(double deltaTime) {
	BaseActor::Tick(deltaTime);
	pointLightComponent.SetPosition({ radius * static_cast<float>(sin(alpha)), 0, radius * static_cast<float>(cos(alpha)) });
	alpha = alpha + deltaTime * rotationSpeed;
}