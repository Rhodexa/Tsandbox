#pragma once
#include <string>
#include "glstuff.h"


class Texture {
private:
	std::string m_Path;
	unsigned int m_TBOID;
	int m_Width, m_Height, m_BPP;

public:
	unsigned char* tex_buffer;

public:
	Texture();
	~Texture();
	void make(const std::string& path);
	void free();
	void bind(unsigned int slot);
	void unbind();
	unsigned int getID() const;
};


