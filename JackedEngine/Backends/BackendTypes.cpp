#include "BackendTypes.h"

BaseResourceReference::BaseResourceReference(const std::string id) :
	id(id)
{}

const std::string BaseResourceReference::GetId() const {
	return id;
}

ImageReference::ImageReference() :
	BaseResourceReference("")
{}

ImageReference::ImageReference(const std::string id) :
	BaseResourceReference(id)
{}

ModelReference::ModelReference() :
	BaseResourceReference("")
{}

ModelReference::ModelReference(const std::string id) : 
	BaseResourceReference(id)
{}

UniformReference::UniformReference(const std::string id) :
	BaseResourceReference(id)
{}

UniformReference::UniformReference() :
	BaseResourceReference("")
{}