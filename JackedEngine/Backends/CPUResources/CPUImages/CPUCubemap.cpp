#include "CPUCubemap.h"

CPUCubemap::CPUCubemap(std::array<std::string, 6> imageFiles) :
	filePaths(imageFiles),
	pixelData({0})
{
	id = "";
	for (unsigned int i = 0; i < imageFiles.size(); i++) {
		id = id + imageFiles[i];
	}
}

CPUCubemap::~CPUCubemap() {
	clearData();
}

void CPUCubemap::LoadData() {
	clearData();
	for (unsigned int i = 0; i < filePaths.size(); i++) {
		pixelData[i] = loadImage(filePaths[i].c_str(), &width, &height, &nChannels);
	}
}

void CPUCubemap::clearData() {
	for (const void* pixels : pixelData) {
		freeImage(const_cast<void*>(pixels));
	}
}

const std::string CPUCubemap::GetId() const {
	return id;
}

const std::array<const void*, 6> CPUCubemap::GetPixelData() const {
	return pixelData;
}

const int CPUCubemap::GetWidth() const {
	return width;
}

const int CPUCubemap::GetHeight() const {
	return height;
}

const int CPUCubemap::GetNChannels() const {
	return nChannels;
}