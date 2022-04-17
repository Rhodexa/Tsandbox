#pragma once
#include "gmath.h"
#include "Object.h"
#include "Textures.h"


class Sprite : public Object {
private:
	unsigned int m_TextureID;
	unsigned int ss_origin_x = 0, ss_origin_y = 0;
	unsigned int ss_w = 1, ss_h = 1;
	unsigned int sprite_w = 0, sprite_h = 0;

public:	
	unsigned int frame_index = 0;
	glm::mat3 sprite_matrix;

public:
	Sprite();
	~Sprite();

	void make(const Texture& texture, unsigned int sheet_w, unsigned int sheet_h, unsigned int _sprite_w, unsigned int _sprite_h,
		unsigned int sprite_origin_x = 0, unsigned int sprite_origin_y = 0, unsigned int sheet_origin_x = 0, unsigned int sheet_origin_y = 0);
	void setFrame(unsigned int frame_index);
};

