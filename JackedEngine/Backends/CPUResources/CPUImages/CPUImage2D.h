#pragma once
#include <string>
#include <vector>
#include "Backends/CPUResources/CPUImages/CPUBaseImage.h"

class CPUImage2D : CPUBaseImage{
public:
	CPUImage2D(std::string imageFile);
	~CPUImage2D();

	void LoadData();
	const std::string GetId() const;

	const void* GetPixelData() const;
	const int GetWidth() const;
	const int GetHeight() const;
	const int GetNChannels() const;

private:
	std::string filePath;
	std::string id;
	const void* pixelData;
	int width;
	int height;
	int nChannels;

	void clearData();
};