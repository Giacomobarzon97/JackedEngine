#include "RenderableObject.h"

RenderableObject::RenderableObject(const Model& model) :
	model(model)
{}

void RenderableObject::Rotate(const double x, const double y, const double z) {

}

void RenderableObject::Translate(const double x, const double y, const double z) {

}

void RenderableObject::Scale(const double x, const double y, const double z) {

}

void RenderableObject::SetPosition(const double x, const double y, const double z) {

}

void RenderableObject::SetRotation(const double x, const double y, const double z) {

}

void RenderableObject::SetScale(const double x, const double y, const double z) {

}

const glm::mat4 RenderableObject::GetModelMatrix() const {
	return modelMatrix;
}

const Model& RenderableObject::GetModel() const {
	return model;
}
