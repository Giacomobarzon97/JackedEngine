#include "GenericMeshMaterial.h"

GenericMeshMaterial::GenericMeshMaterial(const std::string diffuseTexturePath) {
	CPUImage texture(diffuseTexturePath, IMAGE_2D);
	diffuseTextureRef = JackedEngine::GetRenderer().CreateImage(texture);
}

const ImageReference GenericMeshMaterial::GetDiffuseTexture() const {
	return diffuseTextureRef;
}