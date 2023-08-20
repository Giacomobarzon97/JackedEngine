#include "InputManager.h"

InputManager::InputManager(BaseWindow& window) : 
	window(window)
{}

void InputManager::BindCallback(std::function<void(InputKey, InputEvent, float)> binding) {
	window.BindCallback(binding);
}

void InputManager::CreateAxis(std::string id) {
	if (axes.find(id) != axes.end()) {
		throw std::runtime_error("An axis with this name already exists");
	}
	axes[id] = std::vector<std::tuple<InputKey, float>>();
}

void InputManager::AddMappingToaAxis(std::string id, InputKey key, float scaleValue) {
	auto it = axes.find(id);
	if (it == axes.end()) {
		throw std::runtime_error("No axis with this name exists");
	}
	axes[id].push_back({key, scaleValue});
}

std::vector<std::tuple<InputKey, float>> InputManager::GetAxisData(std::string id) const {
	auto it = axes.find(id);
	if (it == axes.end()) {
		throw std::runtime_error("No axis with this name exists");
	}
	return it->second;
}