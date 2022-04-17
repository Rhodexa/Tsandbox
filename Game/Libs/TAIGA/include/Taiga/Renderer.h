#pragma once
#include "glstuff.h"
#include "Object.h"
#include "Material.h"
#include "Sprite.h"

class Renderer {
public:
	// void draw(VertexBuffer& vbo, IndexBuffer& ibo, VertexLayout& vaa, Shader& shader) const;
	void draw(Object& obj, Material& mat) const;
	void draw(Sprite& obj, Shader& shader) const;
};


