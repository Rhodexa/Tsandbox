#pragma once
#include <iostream>
#include "gmath.h"

class Camera {
private:	
	glm::vec3 m_Position;
	glm::vec3 m_Orientation;
	glm::vec3 m_Tilt;

public:
	glm::mat4 view_matrix;

public:
	Camera();
	~Camera();

	void set();
	void setPosition(glm::vec3& pos);
	void setTilt(glm::vec3& tilt);
	void setOrientation(glm::vec3& orientation);
	void setTarget(glm::vec3& target);
};

