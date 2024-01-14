#pragma once
#include <array>
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"

class CPUCubeModel : public CPUBaseModel {
public:
	virtual void LoadData() override;
	virtual const ModelData GetModelData() const override;
	virtual const std::string& GetId() const override;

private:
	static const std::string id;
	static const std::array<uint32_t, 36> indexData;
	static const std::array<CPUPositionVertex, 36> positionData;
	static const std::array<CPUTextureVertex, 36> texCoordData;
	static const std::array<CPUNormalVertex, 36> normalData;

	ModelData data{};
};