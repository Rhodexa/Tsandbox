#pragma once
#include <string>
#include "Shader.h"
#include "Textures.h"

class Material {
public:
	Texture texture;
	Shader shader;

	Material();
	~Material();

	void make(std::string shader_path, std::string texture_path);
	void bind();
	void unbind();
};


