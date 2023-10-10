#include "CPUImage2D.h"

CPUImage2D::CPUImage2D(std::string filePath) :
	filePath(filePath)
{
	id = filePath;
}


CPUImage2D::~CPUImage2D() {
	clearData();
}

void CPUImage2D::LoadData() {
	clearData();
	pixelData = loadImage(filePath.c_str(), &width, &height, &nChannels);
}

void CPUImage2D::clearData() {
	freeImage(const_cast<void*>(pixelData));
}

const std::string CPUImage2D::GetId() const {
	return id;
}

const void* CPUImage2D::GetPixelData() const {
	return pixelData;
}

const int CPUImage2D::GetWidth() const {
	return width;
}

const int CPUImage2D::GetHeight() const {
	return height;
}

const int CPUImage2D::GetNChannels() const {
	return nChannels;
}