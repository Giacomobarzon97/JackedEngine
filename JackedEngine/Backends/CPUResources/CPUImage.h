#pragma once
#include <string>
#include <vector>
#include <stb_image.h>

enum ImageType {
	IMAGE_2D,
	CUBEMAP
};

class CPUImage {
public:
	CPUImage(std::string imageFile, ImageType imageType = IMAGE_2D);
	CPUImage(std::vector<std::string> imageFiles, ImageType imageType = IMAGE_2D);
	~CPUImage();

	void LoadData();
	const std::string GetId() const;

	const std::vector<const void*> GetPixelData() const;
	const int GetWidth() const;
	const int GetHeight() const;
	const int GetNChannels() const;
	const ImageType GetImageType() const;

private:
	void clearData();

	std::vector<std::string> filePaths;
	std::string id;
	std::vector<const void*> pixelData;
	int width;
	int height;
	int nChannels;
	ImageType imageType;
};