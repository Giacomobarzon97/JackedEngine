#pragma once
#include <string>
#include <stb_image.h>

class CPUImage {
public:
	CPUImage(std::string filePath);
	~CPUImage();
	const stbi_uc* const GetPixelData() const;
	const int GetWidth() const;
	const int GetHeight() const;
	const int GetNChannels() const;

private:
	stbi_uc* pixels;
	int width;
	int height;
	int nChannels;
};