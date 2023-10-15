#pragma once
#include <string>

class BaseBackendResourceReference {
public:
	BaseBackendResourceReference(const std::string id);
	const std::string GetId() const;
private:
	std::string id;
};

class BackendPipelineReference : public BaseBackendResourceReference {
public:
	BackendPipelineReference();
	BackendPipelineReference(const std::string id);
};

class BackendModelReference : public BaseBackendResourceReference {
public:
	BackendModelReference();
	BackendModelReference(const std::string id);
};

class BackendImage2DReference : public BaseBackendResourceReference {
public:
	BackendImage2DReference();
	BackendImage2DReference(const std::string id);
};

class BackendCubemapReference : public BaseBackendResourceReference {
public:
	BackendCubemapReference();
	BackendCubemapReference(const std::string id);
};

class BackendUniformReference : public BaseBackendResourceReference {
public:
	BackendUniformReference();
	BackendUniformReference(const std::string id);
};

class BackendStorageBufferReference : public BaseBackendResourceReference {
public:
	BackendStorageBufferReference();
	BackendStorageBufferReference(const std::string id);
};