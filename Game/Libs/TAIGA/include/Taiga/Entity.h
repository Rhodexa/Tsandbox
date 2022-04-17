#pragma once
#include "gmath.h"

class Entity {
private:

public:
	glm::vec3 pos, vel, acc;
	float damping;

	Entity();
	~Entity();
	void bounce(glm::vec3 normal);
};

