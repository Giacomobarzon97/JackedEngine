#include "BackendTypes.h"

BaseBackendResourceReference::BaseBackendResourceReference(const std::string id) :
	id(id)
{}

const std::string BaseBackendResourceReference::GetId() const {
	return id;
}

BackendPipelineReference::BackendPipelineReference() :
	BaseBackendResourceReference("")
{}

BackendPipelineReference::BackendPipelineReference(const std::string id) :
	BaseBackendResourceReference(id)
{}

BackendModelReference::BackendModelReference() :
	BaseBackendResourceReference("")
{}

BackendModelReference::BackendModelReference(const std::string id) :
	BaseBackendResourceReference(id)
{}

BackendImageReference::BackendImageReference() :
	BaseBackendResourceReference("")
{}

BackendImageReference::BackendImageReference(const std::string id) :
	BaseBackendResourceReference(id)
{}

BackendUniformReference::BackendUniformReference(const std::string id) :
	BaseBackendResourceReference(id)
{}

BackendUniformReference::BackendUniformReference() :
	BaseBackendResourceReference("")
{}