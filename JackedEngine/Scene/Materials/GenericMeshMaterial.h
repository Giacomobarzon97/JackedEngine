#pragma once
#include "JackedEngine.h"
#include "Scene/Materials/BaseMaterial.h"

class GenericMeshMaterial : public BaseMaterial{
public:
	GenericMeshMaterial(const std::string diffuseTexturePath);

	const BackendImage2DReference GetDiffuseTexture() const;

private:
	BackendImage2DReference diffuseTextureRef;

};