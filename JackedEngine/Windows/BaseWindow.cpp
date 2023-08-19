#include "BaseWindow.h"

BaseWindow::BaseWindow(uint32_t width, uint32_t height, std::string windowName):
	width(width),
	height(height),
	windowName(windowName)
{}

BaseWindow::~BaseWindow() {}

const std::string BaseWindow::GetWindowName() const{
	return windowName;
}

void BaseWindow::BindCallback(std::function<void(InputKey, InputEvent)> binding) {
	callbacks.push_back(binding);
}