#pragma once
#include "JackedEngine.h"

class BaseMaterial {
public:
	virtual ~BaseMaterial();

	virtual const TextureReference GetDiffuseTexture() const = 0;
};