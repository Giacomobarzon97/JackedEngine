#pragma once
#include "JackedEngine.h"
#include "Scene/Materials/BaseMaterial.h"

class GenericMeshMaterial : public BaseMaterial{
public:
	GenericMeshMaterial(const std::string diffuseTexturePath);

	virtual const BackendImageReference GetDiffuseTexture() const override;
private:
	BackendImageReference diffuseTextureRef;

};