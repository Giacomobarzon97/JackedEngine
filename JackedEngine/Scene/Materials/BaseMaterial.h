#pragma once
#include "Backends/BackendTypes.h"

class BaseMaterial {
public:
	virtual ~BaseMaterial();

	virtual const BackendImageReference GetDiffuseTexture() const = 0;
};