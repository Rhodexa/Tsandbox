#pragma once
#include "glstuff.h"

struct Vertex {
	float position[3];
	float color[4];
	float uv[2];
};

class VertexBuffer {
public:
	VertexBuffer();
	~VertexBuffer();

	unsigned int ID;

	unsigned int make(const float* buffer, unsigned int count);
	void bind() const ;
	void unbind() const;
};



