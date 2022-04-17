#include "Engine.h"
#include "Window.h"

Engine::Engine() : m_Window(nullptr), m_VAOID(0) {}
Engine::~Engine() {
	glfwTerminate();
}

void Engine::init(const char* title, int w, int h) {
	std::cout << "Taiga Engine" << std::endl;

	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to start" << std::endl;
		glfwTerminate();
	}
	
	m_Window = glfwCreateWindow(w, h, title, NULL, NULL);
	if (!m_Window) {
		std::cout << "ERROR: GLFW window creation failed" << std::endl;
		glfwTerminate();
	}
	
	glfwMakeContextCurrent(m_Window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR: Oof... GLEW failed this time" << std::endl;
		glfwTerminate();
	}
	
	glfwSwapInterval(1);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glGenVertexArrays(1, &m_VAOID);
	glBindVertexArray(m_VAOID);

	std::cout << "Startup done." << std::endl;
}

void Engine::pollEvents() {
	glfwPollEvents();
}

void Engine::windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Engine::clear(){
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::update() {
	pollEvents();
	int width, height;
	glfwGetWindowSize(m_Window, &width, &height);
	windowResize(m_Window, width, height);
	glfwSwapBuffers(m_Window);
}
