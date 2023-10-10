#include "CPUBaseImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

CPUBaseImage::~CPUBaseImage() {}

const void* CPUBaseImage::loadImage(char const* filename, int* x, int* y, int* comp) {
	return stbi_load(filename, x, y, comp, STBI_rgb_alpha);
}

void CPUBaseImage::freeImage(void* pixels) {
	stbi_image_free(pixels);
}