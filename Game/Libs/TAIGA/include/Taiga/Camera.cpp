#include "Camera.h"

Camera::Camera() :
	m_Position({ 0.0, 0.0, 0.0 }),
	m_Orientation({0.0, 0.0, 1.0}),
	m_Tilt({ 0.0, 1.0, 0.0 }),
	view_matrix({
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	})
{}
Camera::~Camera() {}

void Camera::set() {
	//glm::vec3 handle_z = m_Orientation; - If  handle_x and m_Orientation are the same, why copy? (Z ad orientation are both the vector that represents the camera direction)
	glm::vec3 handle_x = glm::normalize(glm::cross(m_Tilt, m_Orientation));
	glm::vec3 handle_y = glm::cross(m_Orientation, handle_x);

	view_matrix = {
		 handle_x.x, handle_y.x, m_Orientation.x, 0,
		 handle_x.y, handle_y.y, m_Orientation.y, 0,
		 handle_x.z, handle_y.z, m_Orientation.z, 0,
		 -glm::dot(handle_x, m_Position), -glm::dot(handle_y, m_Position), -glm::dot(m_Orientation, m_Position),  1
	};
}

void Camera::setPosition(glm::vec3& pos) {
	m_Position = pos;
	set();
}

void Camera::setTilt(glm::vec3& tilt) {
	m_Tilt = tilt;
	set();
}

void Camera::setOrientation(glm::vec3& orientation) {
	m_Orientation = glm::normalize(orientation);
	set();
}

void Camera::setTarget(glm::vec3& target) {
	m_Orientation = glm::normalize(target - m_Position);
	set();
}