#pragma once
#include "Scene/Components/SceneComponent.h"
#include "JackedEngine.h"

class BaseLightComponent : public SceneComponent {
public:
	BaseLightComponent(ComponentInitializer initializer);

	virtual void Init() override;
	virtual void Tick(double deltaTime) override;

protected:
	RendererLightReference lightReference;
};