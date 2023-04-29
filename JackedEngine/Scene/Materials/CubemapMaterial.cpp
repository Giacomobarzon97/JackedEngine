#include "CubemapMaterial.h"

CubemapMaterial::CubemapMaterial(const std::string front, const std::string back, const std::string top, const std::string bottom, const std::string right, const std::string left) {
	CPUImage texture({ front, back, top, bottom, right, left }, CUBEMAP);
	diffuseTextureRef = JackedEngine::GetRenderer().CreateTexture(texture);
}

const TextureReference CubemapMaterial::GetDiffuseTexture() const {
	return diffuseTextureRef;
}