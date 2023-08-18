#pragma once
#include <string>
#include <glm/glm.hpp>
class BaseActor;

struct ComponentInitializer {
	std::string name;
	BaseActor* actorOwner;
};

class BaseComponent {
public:
	BaseComponent(ComponentInitializer initializer);
	virtual ~BaseComponent();
	
	virtual void Init();
	virtual void Tick(double deltaTime);

	const std::string GetName();
	BaseActor& GetActorOwner();

private:
	std::string name;
	BaseActor* actorOwner;
};