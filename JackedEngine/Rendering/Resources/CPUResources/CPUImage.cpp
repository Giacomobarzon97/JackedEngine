#include "CPUImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

CPUImage::CPUImage(std::string filePath) :
	pixels(stbi_load(filePath.c_str(), &width, &height, &nChannels, STBI_rgb_alpha))
{}

CPUImage::~CPUImage() {
	stbi_image_free(pixels);
}


const stbi_uc* const CPUImage::GetPixelData() const {
	return pixels;
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