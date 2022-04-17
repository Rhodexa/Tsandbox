#include "IndexBuffer.h"
#include <iostream>

IndexBuffer::IndexBuffer() : ID(0) {}
IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &ID);
}

unsigned int IndexBuffer::make(const unsigned int* buffer, unsigned int count) {
	if (!ID) glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(buffer), buffer, GL_STATIC_DRAW);
	return ID;
}
void IndexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
