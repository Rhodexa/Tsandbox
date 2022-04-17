#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer() : ID(0) {}
VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &ID);
}

unsigned int VertexBuffer::make(const float* buffer, unsigned int count) {
	if (!ID) glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), buffer, GL_DYNAMIC_DRAW);
	return ID;
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
