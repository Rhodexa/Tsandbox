#include "Sprite.h"

Sprite::Sprite() :
	m_TextureID(0), 
	sprite_matrix({
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 
		0.0, 0.0, 1.0
	})
{}
Sprite::~Sprite() {}

void Sprite::make(const Texture& texture, unsigned int sheet_w, unsigned int sheet_h, unsigned int _sprite_w, unsigned int _sprite_h,
		unsigned int sprite_origin_x, unsigned int sprite_origin_y, unsigned int sheet_origin_x, unsigned int sheet_origin_y) {

	m_TextureID = texture.getID();
	if(sheet_w != 0) ss_w = sheet_w;
	if(sheet_h != 0) ss_h = sheet_h;
	sprite_w = _sprite_w; 
	sprite_h = _sprite_h;
	ss_origin_x = sheet_origin_x;
	ss_origin_y = sheet_origin_y;

	float vertices[16] {
		float(sprite_origin_x),            float(sprite_origin_y),            0.0f,		    0.0f,
		float(sprite_origin_x) + sprite_w, float(sprite_origin_y),            1.0f / sheet_w, 0.0f,
		float(sprite_origin_x) + sprite_w, float(sprite_origin_y + sprite_h), 1.0f / sheet_w, 1.0f / sheet_h,
		float(sprite_origin_x),			   float(sprite_origin_y + sprite_h), 0.0f,		    1.0f / sheet_h
	};
	unsigned int indices[6] {0, 1, 2, 2, 3, 0};

	vbo.make(vertices, 16);
	vaa.append(2);
	vaa.append(2);	
	vaa.build(vbo);	
	ibo.make(indices, 6);

	setFrame(0);
}

void Sprite::setFrame(unsigned int frame_index) {
	float x_offset = float(frame_index % ss_w);
	float y_offset = float(floor(frame_index / ss_w));
	sprite_matrix = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		x_offset/ss_w, y_offset/ss_h, 1.0
	};
}