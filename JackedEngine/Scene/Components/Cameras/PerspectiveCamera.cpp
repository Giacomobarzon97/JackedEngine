#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(ComponentInitializer initializer) :
	BaseCameraComponent(initializer)
{}

void PerspectiveCamera::Init() {
	BaseCameraComponent::Init();
}

void PerspectiveCamera::Tick(double deltaTime) {
	BaseCameraComponent::Tick(deltaTime);
	glm::vec3 eye = GetPosition();
	glm::vec3 look = eye;
	look += glm::vec3({ 1, 0, 0 });
	glm::vec3 up = GetUpVector();

	m_n = glm::normalize(eye - look);
	m_u = glm::normalize(glm::cross(up, m_n));
	m_v = glm::normalize(glm::cross(m_n, m_u));

	glm::vec3 rotation = GetRotation();

	rotAxes(m_u, m_v, -rotation.x);
	rotAxes(m_n, m_v, rotation.y);
	rotAxes(m_u, m_n, rotation.z);
}

const glm::vec3 PerspectiveCamera::getXAxis() const{
	return 	m_n;
}

const glm::vec3 PerspectiveCamera::getYAxis() const {
	return 	m_u;
}

const glm::vec3 PerspectiveCamera::getZAxis() const {
	return 	m_v;
}

const glm::mat4 PerspectiveCamera::GetViewMatrix() const {
	glm::vec3 eye = GetPosition();

	glm::mat4 view{
		{m_u.x, m_v.x, m_n.x, 0},
		{m_u.y, m_v.y, m_n.y, 0},
		{m_u.z, m_v.z, m_n.z, 0},
		{-glm::dot(-eye,m_u), -glm::dot(-eye,m_v), -glm::dot(-eye,m_n), 1}
	};

	return view;
}

void PerspectiveCamera::rotAxes(glm::vec3& io_a, glm::vec3& io_b, double angle) {
	double rad = glm::radians(angle);

	double c = cos(rad);
	double s = sin(rad);

	glm::vec3 t{
		c* io_a.x + s * io_b.x, 
		c* io_a.y + s * io_b.y, 
		c* io_a.z + s * io_b.z
	};

	io_b = {
		-s * io_a.x + c * io_b.x,
		-s * io_a.y + c * io_b.y,
		-s * io_a.z + c * io_b.z
	};
	io_a = t;
}

const glm::mat4 PerspectiveCamera::GetProjectionMatrix(const uint32_t width, const uint32_t height) const {
	glm::mat4 proj = glm::perspective(glm::radians(fov), width / (float)height, 0.1f, 10.0f);
	proj[1][1] *= -1;
	return proj;
}