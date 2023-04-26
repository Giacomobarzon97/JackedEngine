#include "GenericMeshMaterial.h"

GenericMeshMaterial::GenericMeshMaterial(const std::string diffuseTexturePath) {
	CPUImage texture(diffuseTexturePath, IMAGE_2D);
	diffuseTextureRef = JackedEngine::Renderer().CreateTexture(texture);
}

const TextureReference GenericMeshMaterial::GetDiffuseTexture() const {
	return diffuseTextureRef;
}