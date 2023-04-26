#pragma once
#include "Scene/Materials/BaseMaterial.h"

class GenericMeshMaterial : public BaseMaterial{
public:
	GenericMeshMaterial(const std::string diffuseTexturePath);

	virtual const TextureReference GetDiffuseTexture() const override;
private:
	TextureReference diffuseTextureRef;

};