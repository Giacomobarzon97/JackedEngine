#pragma once
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"

class CPUGenericMesh : public CPUBaseModel {
public:
	CPUGenericMesh(const std::string objPath);
	virtual void LoadData() override;
	virtual const ModelData GetModelData() const override;
	virtual const std::string& GetId() const override;

private:
	const std::string objPath;

	std::vector<CPUPositionVertex> positions;
	std::vector<CPUTextureVertex> texCoords;
	std::vector<CPUNormalVertex> normals;
	std::vector<uint32_t> indices;
};