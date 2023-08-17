#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(std::string name) :
	BaseCameraComponent(name)
{}

void PerspectiveCamera::Init() {
	BaseCameraComponent::Init();
	Translate(2, 2, 2);
}

void PerspectiveCamera::Tick(double deltaTime) {
	BaseCameraComponent::Tick(deltaTime);
	Rotate(0, 100 * deltaTime, 0);
}

const glm::mat4 PerspectiveCamera::GetViewMatrix() const {
	glm::vec3 eye{ xTrans, yTrans, zTrans };
	glm::vec3 look{ xTrans + 1, yTrans, zTrans };
	glm::vec3 up = upVector;

	glm::vec3 m_n = glm::normalize(eye - look);
	glm::vec3 m_u = glm::normalize(glm::cross(up,m_n));
	glm::vec3 m_v = glm::normalize(glm::cross(m_n,m_u));

	rotAxes(m_u,m_v, - roll);
	rotAxes(m_n, m_v, pitch);
	rotAxes(m_u, m_n, yaw);

	glm::mat4 view{
		{m_u.x, m_v.x, m_n.x, 0},
		{m_u.y, m_v.y, m_n.y, 0},
		{m_u.z, m_v.z, m_n.z, 0},
		{-glm::dot(-eye,m_u), -glm::dot(-eye,m_v), -glm::dot(-eye,m_n), 1}
	};

	return view;
}

void PerspectiveCamera::rotAxes(glm::vec3& io_a, glm::vec3& io_b, double angle) {
	double c = cosf(angle);
	double s = sinf(angle);
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
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), width / (float)height, 0.1f, 10.0f);
	proj[1][1] *= -1;
	return proj;
}