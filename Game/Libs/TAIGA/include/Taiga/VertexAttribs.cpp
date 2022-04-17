#include "VertexAttribs.h"

VertexLayout::VertexLayout() : m_Stride(0) {}
VertexLayout::~VertexLayout() {}

void VertexLayout::append(unsigned int count) {
	m_Attributes.push_back({ GL_FLOAT, count, GL_FALSE });
	m_Stride += sizeOf(GL_FLOAT) * count;
}

void VertexLayout::build(const VertexBuffer& vbo) {
	vbo.bind();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < m_Attributes.size(); i++) {
		const VertexAttribute &attrib = m_Attributes[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalize, m_Stride, (const void*)(offset));
		offset += sizeOf(attrib.type) * attrib.count;
	}
}

void VertexLayout::bind(const VertexBuffer& vbo) {
	vbo.bind();
	for (unsigned int i = 0; i < m_Attributes.size(); i++) {
		glEnableVertexAttribArray(i);
	}
}

void VertexLayout::unbind(const VertexBuffer& vbo) {
	vbo.bind();
	for (unsigned int i = 0; i < m_Attributes.size(); i++) {
		glDisableVertexAttribArray(i);
	}
}
