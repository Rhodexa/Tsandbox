#pragma once
#include "glstuff.h"

class IndexBuffer {
private:

public:
	IndexBuffer();
	~IndexBuffer();

	unsigned int ID;

	unsigned int make(const unsigned int* buffer, unsigned int count);
	void bind() const;
	void unbind() const;
};


