#include "TaigaCore.h"

// There are probably much better ways than this to do the same thing. Defining macros is just weird. MaKe_TAigA_ApP ñi ñi ñi
extern Taiga* getApplication();
Taiga::Taiga() : windowName("Taiga Engine v0.9.34.170422") {std::cout << "Taiga Core Created!\n";}
Taiga::Taiga(const char* window_name) : windowName(window_name) {std::cout << "Taiga Core Created!\n";}
Taiga::~Taiga() {}

// define this to tell Taiga not to touch your beloved int main(){}
#ifndef TGA_LEMME_DO_IT_MY_WAY
int main(int argc, char** args) {
	Taiga* taiga = getApplication();

	taiga->init(taiga->windowName, 1024, 720);
	taiga->setup();

	while (!glfwWindowShouldClose(taiga->m_Window)) {
		glfwGetCursorPos(taiga->m_Window, &taiga->mouseX, &taiga->mouseY);
		glfwGetWindowSize(taiga->m_Window, &taiga->windowWidth, &taiga->windowHeight);
		taiga->mouseX = taiga->mouseX - taiga->windowWidth / 2;
		taiga->mouseY = -taiga->mouseY + taiga->windowHeight / 2;

		taiga->clear();
		taiga->draw();
		taiga->update();
	}

	delete taiga;
	glfwTerminate();
	return 0;
}
#endif

void Taiga::setup() {}
void Taiga::draw() {}


