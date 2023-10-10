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

BackendImage2DReference::BackendImage2DReference() :
	BaseBackendResourceReference("")
{}

BackendImage2DReference::BackendImage2DReference(const std::string id) :
	BaseBackendResourceReference(id)
{}

BackendCubemapReference::BackendCubemapReference() :
	BaseBackendResourceReference("")
{}

BackendCubemapReference::BackendCubemapReference(const std::string id) :
	BaseBackendResourceReference(id)
{}

BackendUniformReference::BackendUniformReference(const std::string id) :
	BaseBackendResourceReference(id)
{}

BackendUniformReference::BackendUniformReference() :
	BaseBackendResourceReference("")
{}