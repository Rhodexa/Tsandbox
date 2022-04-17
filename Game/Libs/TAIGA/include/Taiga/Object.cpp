#include "Object.h"

Object::Object() {}
Object::~Object() {}

void Object::make(const float* vertices, unsigned int v_count, const unsigned int* indices, unsigned int i_count) {
	vbo.make(vertices, v_count); // Load the vertex buffer to the GPU
	vaa.append(2);				 // vertex components layout: Vertex pos X, Y at location 0
	vaa.append(2);				 // vertex components layout: Texture Coordinates U, V at location 1
	vaa.build(vbo);				 // load the vertex components to the GPU
	ibo.make(indices, i_count);	 // Load the index buffer to the GPU
}
