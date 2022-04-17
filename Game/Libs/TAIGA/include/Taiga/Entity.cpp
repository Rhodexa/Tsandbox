#include "Entity.h"
Entity::Entity() :
	pos({ 0.0, 0.0, 0.0 }), 
	vel({ 0.0, 0.0, 0.0 }),
	acc({ 0.0, 0.0, 0.0 })
{}

Entity::~Entity() {}

void Entity::bounce(glm::vec3 normal) {
	vel = vel - 2 * (glm::dot(vel, normal)) * normal;
}