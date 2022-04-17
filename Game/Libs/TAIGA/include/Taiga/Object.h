#pragma once
#include "glstuff.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexAttribs.h"
#include "Textures.h"
#include "Shader.h"

class Object {
public:
	VertexBuffer vbo;
	IndexBuffer ibo;
	VertexLayout vaa;

public:
	Object();
	~Object();

	void make(const float* vertices, unsigned int v_count, const unsigned int* indices, unsigned int i_count);
};


