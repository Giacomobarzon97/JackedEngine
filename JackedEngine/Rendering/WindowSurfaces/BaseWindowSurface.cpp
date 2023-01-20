#include "BaseWindowSurface.h"

BaseWindowSurface::~BaseWindowSurface(){}

VkSurfaceKHR* BaseWindowSurface::getVkSurface() {
	return &surface;
}