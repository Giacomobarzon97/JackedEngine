#pragma once
#include <string>
#include <vector>

class CPUBaseImage {
public:
	virtual ~CPUBaseImage();
	virtual const int GetWidth() const = 0;
	virtual const int GetHeight() const = 0;
	virtual const int GetNChannels() const = 0;

protected:
	const void* loadImage(char const* filename, int* x, int* y, int* comp);
	void freeImage(void* pixels);
};