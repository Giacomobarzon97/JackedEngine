#pragma once
#include <string>

class BaseResourceReference {
public:
	BaseResourceReference(const std::string id);
	const std::string GetId() const;
private:
	std::string id;
};

class PipelineReference : public BaseResourceReference {
public:
	PipelineReference();
	PipelineReference(const std::string id);
};

class ModelReference : public BaseResourceReference {
public:
	ModelReference();
	ModelReference(const std::string id);
};

class ImageReference : public BaseResourceReference {
public:
	ImageReference();
	ImageReference(const std::string id);
};

class UniformReference : public BaseResourceReference {
public:
	UniformReference();
	UniformReference(const std::string id);
};