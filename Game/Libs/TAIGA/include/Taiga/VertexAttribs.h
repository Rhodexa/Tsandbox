#pragma once
#include "glstuff.h"
#include "VertexBuffer.h"
#include <vector>

class VertexAttribute {
public:
	unsigned int type;
	unsigned int count;
	unsigned int normalize;
};

class VertexLayout {
private:
	unsigned int m_Stride;
	std::vector<VertexAttribute> m_Attributes;

private:
	static unsigned int sizeOf(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		return 0;
	}	

public:
	VertexLayout();
	~VertexLayout();
	
	void append(unsigned int count);
	void build(const VertexBuffer& vbo);
	void bind(const VertexBuffer& vbo);
	void unbind(const VertexBuffer& vbo);
};


