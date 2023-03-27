#include "GPUCubemap.h"

GPUCubemap::GPUCubemap(const BaseAllocationFactory& allocationFactory, const CPUImage& frontFaceData, const CPUImage& backFaceData, const CPUImage& upFaceData, const CPUImage& downFaceData, const CPUImage& rightFaceData, const CPUImage& leftFaceData) {
	cubemapBuffer = allocationFactory.CreateCubemapBufferAllocation(
		frontFaceData.GetPixelData(),
		backFaceData.GetPixelData(),
		upFaceData.GetPixelData(),
		downFaceData.GetPixelData(),
		rightFaceData.GetPixelData(),
		leftFaceData.GetPixelData(),
		frontFaceData.GetWidth(),
		frontFaceData.GetHeight()
	);
	
	std::array<CPUPositionVertex, 8> positions{
		CPUPositionVertex({-1, -1, -1, 1}),
		CPUPositionVertex({1, -1, -1, 1}),
		CPUPositionVertex({1, 1, -1, 1}),
		CPUPositionVertex({-1, 1, -1, 1}),
		CPUPositionVertex({-1, -1, 1, 1}),
		CPUPositionVertex({1, -1, 1, 1}),
		CPUPositionVertex({1, 1, 1, 1}),
		CPUPositionVertex({-1, 1, 1, 1})
	};

	std::array<uint32_t, 36> indices{
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};

	positionsBufferAllocation = allocationFactory.CreateVertexBufferAllocation(
		positions.data(),
		sizeof(positions)
	);

	indexBufferAllocation = allocationFactory.CreateIndexBufferAllocation(
		indices.data(),
		sizeof(indices)
	);
}

GPUCubemap::~GPUCubemap() {
	delete cubemapBuffer;
	delete positionsBufferAllocation;
	delete indexBufferAllocation;
}

const VkImageView& GPUCubemap::GetImageView() const {
	return cubemapBuffer->GetImageView();
}

const BaseVertexBufferAllocation& GPUCubemap::GetPositionsBufferAllocation() const {
	return *positionsBufferAllocation;
}

const BaseIndexBufferAllocation& GPUCubemap::GetIndexBufferAllocation() const {
	return *indexBufferAllocation;
}

const uint32_t GPUCubemap::GetNumberOfIndices() const {
	return 36;
}