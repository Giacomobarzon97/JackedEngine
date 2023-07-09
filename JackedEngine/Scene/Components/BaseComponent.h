#pragma once
#include <string>
#include <glm/glm.hpp>

class BaseComponent {
public:
	BaseComponent(std::string name);
	virtual ~BaseComponent();
	
	virtual void Init();
	virtual void Tick(double deltaTime);

	const std::string GetName();

protected:
	std::string name;
};