#include "Material.h"

Material::Material() {}
Material::~Material() {}

void Material::make(std::string shader_path, std::string texture_path) {
	shader.make(shader_path);
	texture.make(texture_path);
}

void Material::bind() {
	shader.bind();
	texture.bind(0);
	shader.setUniform1i("u_Texture", 0);
}

void Material::unbind() {
	texture.unbind();
	shader.unbind();
}
