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

class BackendImageReference : public BaseBackendResourceReference {
public:
	BackendImageReference();
	BackendImageReference(const std::string id);
};

class BackendUniformReference : public BaseBackendResourceReference {
public:
	BackendUniformReference();
	BackendUniformReference(const std::string id);
};