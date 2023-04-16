#include "CPUImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

CPUImage::CPUImage(std::string filePath, ImageType imageType) :
	imageType(imageType),
	filePaths(1)
{
	filePaths[0] = filePath;
	id = filePath;
}

CPUImage::CPUImage(std::vector<std::string> imageFiles, ImageType imageType) :
	imageType(imageType),
	filePaths(imageFiles)
{
	id = "";
	for (unsigned int i = 0; i < imageFiles.size(); i++) {
		id = id + imageFiles[i];
	}
}

CPUImage::~CPUImage() {
	clearData();
}

void CPUImage::LoadData() {
	clearData();
	pixelData.clear();
	pixelData.resize(filePaths.size());

	for (unsigned int i = 0; i < filePaths.size(); i++) {
		pixelData[i] = stbi_load(filePaths[i].c_str(), &width, &height, &nChannels, STBI_rgb_alpha);
	}
}

void CPUImage::clearData() {
	for (const void* pixels : pixelData) {
		stbi_image_free(const_cast<void*>(pixels));
	}
}

const std::string CPUImage::GetId() const {
	return id;
}

const std::vector<const void* > const CPUImage::GetPixelData() const {
	return pixelData;
}

const int CPUImage::GetWidth() const {
	return width;
}

const int CPUImage::GetHeight() const {
	return height;
}

const int CPUImage::GetNChannels() const {
	return nChannels;
}

const ImageType CPUImage::GetImageType() const {
	return imageType;
}