#pragma once
#include <string>
#include <iostream>
#include "glstuff.h"
#include "Renderer.h"

class Engine {
public:
	GLFWwindow* m_Window;

public:
	unsigned int m_VAOID;
	float mouseX = 0;
	float mouseY = 0;

public:
	Engine();
	~Engine();

	void init(const char*, int, int);
	void pollEvents();
	void windowResize(GLFWwindow* window, int width, int height);
	void clear();
	void update();
};


