#pragma once
#include "Backends/BackendTypes.h"
#include "JackedEngine.h"

class BaseMaterial {
public:
	BaseMaterial(std::string name);
	virtual ~BaseMaterial();

	std::string GetName() const;
	const RendererMaterialUniformReference GetMaterialReference() const;

	void SetAmbientReflectionCoefficients(glm::vec3 coeffients);
	void SetDiffuseReflectionCoefficients(glm::vec3 coeffients);
	void SetSpecularReflectionCoefficients(glm::vec3 coeffients);

private:
	std::string name;
	RendererMaterialUniformReference materialReference;

};