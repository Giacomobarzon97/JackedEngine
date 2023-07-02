#pragma once
#include <string>
#include <glm/glm.hpp>

class BaseComponent {
public:
	BaseComponent(std::string name);
	virtual ~BaseComponent();
	
	virtual void Init() = 0;

	const std::string GetName();

protected:
	std::string name;
};