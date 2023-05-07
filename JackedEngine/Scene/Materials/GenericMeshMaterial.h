#pragma once
#include "JackedEngine.h"
#include "Scene/Materials/BaseMaterial.h"

class GenericMeshMaterial : public BaseMaterial{
public:
	GenericMeshMaterial(const std::string diffuseTexturePath);

	virtual const ImageReference GetDiffuseTexture() const override;
private:
	ImageReference diffuseTextureRef;

};