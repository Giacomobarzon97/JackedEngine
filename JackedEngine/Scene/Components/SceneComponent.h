#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "Scene/Components/BaseComponent.h"

class SceneComponent : public BaseComponent {
public:
	virtual void Rotate(const double x, const double y, const double z) = 0;
	virtual void Translate(const double x, const double y, const double z) = 0;
	virtual void Scale(const double x, const double y, const double z) = 0;
	virtual void SetPosition(const double x, const double y, const double z) = 0;
	virtual void SetRotation(const double x, const double y, const double z) = 0;
	virtual void SetScale(const double x, const double y, const double z) = 0;
};