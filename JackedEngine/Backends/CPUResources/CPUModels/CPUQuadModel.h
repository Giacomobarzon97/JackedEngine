#pragma once
#include <array>
#include "Backends/CPUResources/CPUModels/CPUBaseModel.h"

class CPUQuadModel : public CPUBaseModel {
public:
	virtual void LoadData() override;
	virtual const ModelData GetModelData() const override;
	virtual const std::string& GetId() const override;

private:
	static const std::string id;
	static const std::array<uint32_t, 6> indexData;
	static const std::array<CPUPositionVertex, 4> positionData;
	static const std::array<CPUTextureVertex, 4> texCoordData;
	static const std::array<CPUNormalVertex, 4> normalData;

	ModelData data{};
};