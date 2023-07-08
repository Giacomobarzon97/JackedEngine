#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/BaseComponent.h"

class SceneComponent : public BaseComponent {
public:
	SceneComponent(std::string name);

	virtual void Init();
	virtual void Tick();

	void Translate(const double x, const double y, const double z);
	void Rotate(const double x, const double y, const double z);
	void Scale(const double x, const double y, const double z);
	void SetPosition(const double x, const double y, const double z);
	void SetRotation(const double x, const double y, const double z);
	void SetScale(const double x, const double y, const double z);

protected:
	uint32_t xTrans, yTrans, zTrans;
	uint32_t xRot, yRot, zRot;
	uint32_t xScale, yScale, zScale;

};