#pragma once
#include <iostream>
#include <string>
#include "glstuff.h"
#include "Engine.h"
#include "Object.h"
#include "Textures.h"
#include "Shader.h"

class Taiga : public Engine {
private:

public:
	const char* windowName;
	double mouseX = 0, mouseY = 0;
	int windowWidth = 0, windowHeight = 0;

public:
	Taiga();
	Taiga(const char*);
	~Taiga();
	virtual void setup();
	virtual void draw();
};

#define MAKE_TAIGA_APP(app) Taiga* getApplication() { app* taiga = new app; return taiga; }