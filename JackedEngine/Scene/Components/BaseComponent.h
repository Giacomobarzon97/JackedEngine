#pragma once
#include <string>
#include <glm/glm.hpp>

class BaseComponent {
public:
	BaseComponent(const std::string name);
	virtual ~BaseComponent() = 0;

	const std::string GetName() const;

private:
	std::string name;
};