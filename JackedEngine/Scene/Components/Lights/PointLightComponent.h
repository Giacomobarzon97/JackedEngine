#pragma once
#include "Scene/Components/Lights/BaseLightComponent.h"
#include "JackedEngine.h"

class PointLightComponent : public BaseLightComponent {
public:
	PointLightComponent(ComponentInitializer initializer);

	virtual void Init() override;
	virtual void Tick(double deltaTime) override;

private:
	RendererPointLightReference pointLightReference;
};