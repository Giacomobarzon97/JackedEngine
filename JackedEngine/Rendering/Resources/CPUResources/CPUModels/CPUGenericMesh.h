#pragma once
#include "Rendering/Resources/CPUResources/CPUModels/CPUBaseModel.h"

class CPUGenericMesh : public CPUBaseModel {
public:
	CPUGenericMesh(const std::string objPath, const bool includePositions = true, const bool includeTexcoords = true);
	virtual void LoadData() override;
	virtual const ModelData GetModelData() const override;
	virtual const std::string& GetId() const override;

private:
	const bool includePositions;
	const bool includeTexcoords;
	const std::string objPath;

	std::vector<CPUPositionVertex> positions;
	std::vector<CPUTextureVertex> texCoords;
	std::vector<uint32_t> indices;
};