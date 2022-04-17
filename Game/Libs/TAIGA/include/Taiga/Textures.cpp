#include "Textures.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture() : m_TBOID(0), tex_buffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {}

Texture::~Texture() {
	if (tex_buffer)
		stbi_image_free(tex_buffer);
	glDeleteTextures(1, &m_TBOID);
}

void Texture::make(const std::string& path) {
	m_Path = path;
	stbi_set_flip_vertically_on_load(1);
	tex_buffer = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_TBOID);
	if (!m_TBOID) std::cout << "Failed to gen Texture" << "\n";
	glBindTexture(GL_TEXTURE_2D, m_TBOID);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_buffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::free() {
	if (tex_buffer)
		stbi_image_free(tex_buffer);
}

void Texture::bind(unsigned int slot = 0) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TBOID);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getID() const {
	return m_TBOID;
}