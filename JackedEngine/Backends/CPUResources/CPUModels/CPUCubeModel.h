#pragma once
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"

class CPUCubeModel : public CPUBaseModel {
public:
	CPUCubeModel(const bool includePositions = true, const bool includeTexcoords = true);

	virtual void LoadData() override;
	virtual const ModelData GetModelData() const override;
	virtual const std::string& GetId() const override;

private:
	const bool includePositions;
	const bool includeTexcoords;

	static const std::string id;
	static const std::vector<uint32_t> indexData;
	static const std::vector<CPUPositionVertex> positionData;
	static const std::vector<CPUTextureVertex> texCoordData;
};