#include "BaseSceneObject.h"

BaseSceneObject::BaseSceneObject(const std::string name) :
	name(name)
{}

BaseSceneObject::~BaseSceneObject() {}

const std::string BaseSceneObject::GetName() const{
	return name;
}