#pragma once
#include "Scene/Materials/BaseMaterial.h"
#include "JackedEngine.h"

class CubemapMaterial : public BaseMaterial {
public:
	CubemapMaterial(const std::string name, const std::string front, const std::string back, const std::string top, const std::string bottom, const std::string right, const std::string left);

	const RendererCubemapReference GetDiffuseTexture() const;

private:
	RendererCubemapReference diffuseTextureRef;

};