#include "Renderer.h"

//void Renderer::draw(VertexBuffer &vbo, IndexBuffer& ibo, VertexLayout &vaa, Shader& shader) const {
//	shader.bind();
//	ibo.bind();
//	vbo.bind();
//	vaa.bind(vbo);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//}

void Renderer::draw(Object& obj, Material& mat) const {
	obj.vbo.bind();
	obj.vaa.bind(obj.vbo);
	obj.ibo.bind();
	mat.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::draw(Sprite& obj, Shader& shader) const {
	obj.vbo.bind();
	obj.vaa.bind(obj.vbo);
	obj.ibo.bind();
	shader.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

