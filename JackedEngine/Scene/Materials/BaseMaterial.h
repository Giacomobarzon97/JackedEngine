#pragma once
#include "Backends/BackendTypes.h"

class BaseMaterial {
public:
	virtual ~BaseMaterial();

	virtual const ImageReference GetDiffuseTexture() const = 0;
};