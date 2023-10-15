#pragma once
#include "JackedEngine.h"
#include "Scene/Materials/BaseMaterial.h"

class GenericMeshMaterial : public BaseMaterial{
public:
	GenericMeshMaterial(const std::string diffuseTexturePath);

	const RendererImage2DReference GetDiffuseTexture() const;

private:
	RendererImage2DReference diffuseTextureRef;

};