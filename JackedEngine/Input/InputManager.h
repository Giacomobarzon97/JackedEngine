#pragma once
#include <unordered_map>
#include <stdexcept>
#include <tuple>
#include "Windows/BaseWindow.h"

class InputManager {
public:
	InputManager(BaseWindow& window);
	void BindCallback(std::function<void(InputKey, InputEvent, float)> binding);
	void CreateAxis(std::string id);
	void AddMappingToaAxis(std::string id, InputKey key, float scaleValue);
	std::vector<std::tuple<InputKey, float>> GetAxisData(std::string id) const;

private:
	BaseWindow& window;
	std::unordered_map<std::string, std::vector<std::tuple<InputKey, float>>> axes;
};