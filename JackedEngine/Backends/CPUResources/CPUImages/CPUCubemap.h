#pragma once
#include <string>
#include <array>
#include "Backends/CPUResources/CPUImages/CPUBaseImage.h"

class CPUCubemap : CPUBaseImage {
public:
	CPUCubemap(std::array<std::string, 6> imageFiles);
	~CPUCubemap();

	void LoadData();
	const std::string GetId() const;

	const std::array<const void*, 6> GetPixelData() const;
	const int GetWidth() const;
	const int GetHeight() const;
	const int GetNChannels() const;

private:
	void clearData();

	std::array<std::string, 6> filePaths;
	std::string id;
	std::array<const void*, 6> pixelData;
	int width;
	int height;
	int nChannels;
};