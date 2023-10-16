#include "CubemapMaterial.h"

CubemapMaterial::CubemapMaterial(const std::string name, const std::string front, const std::string back, const std::string top, const std::string bottom, const std::string right, const std::string left) :
	BaseMaterial(name)
{
	CPUCubemap texture({ front, back, top, bottom, right, left });
	diffuseTextureRef = JackedEngine::GetRenderer().CreateCubemap(texture);
}

const RendererCubemapReference CubemapMaterial::GetDiffuseTexture() const {
	return diffuseTextureRef;
}