#pragma once
#include <string>
#include <glm/glm.hpp>

class BaseComponent {
public:
	virtual ~BaseComponent();
	
	virtual void Init() = 0;
};