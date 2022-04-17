#include "Taiga/Taiga.h"

// The game it self is a class.
class Game : public Taiga {
public:
	Game() {std::cout << "Conifer Created!\n";}
	~Game() {}
	void draw() override;
	void setup() override;

public:
	Renderer renderer;
	Shader shader;
	Camera camera;
	Sprite sprite;
	Texture sprite_sheet;
	glm::vec3 cam_pos = { 0.0, 0.0, -500.0 };
	glm::vec3 cam_dir = { 0, 0, 1.0 };

	float inter_frame = 0;
};
MAKE_TAIGA_APP(Game);


// This runs once
void Game::setup() {
	// These paths aint necesarily right anymore, they are most likely different now.
	sprite_sheet.make("res/luma/luma.png");
	sprite_sheet.bind(0); // bind the sprite sheet in the GPU's texture slot 0
	sprite.make(sprite_sheet, 2, 3, 100, 100);
	shader.make("../Shaders/basic_shader.shader");
	camera.setPosition(cam_pos);
	camera.setOrientation(cam_dir);
}

// This runs at 60FPS (I guess, we gotta test that)
float cam_vel_y = 0.0;
float floor_y = 100;
bool jump_pressed = false;
void Game::draw() {
		glm::mat4 proj = glm::perspectiveLH(1.2, double(windowWidth)/double(windowHeight), -1.0, 1.0);
		glm::mat4 view = camera.view_matrix;

		// pass matrices to our shader
		shader.setUniformMat3f("UV_MAP", sprite.sprite_matrix);		
		shader.setUniformMat4f("MVP", proj * view);

		inter_frame += 0.2f;
		if (cam_pos.y >= floor_y) {
			if(glfwGetKey(m_Window, GLFW_KEY_A) || glfwGetKey(m_Window, GLFW_KEY_D))
					sprite.setFrame(((unsigned int)inter_frame) % 6);
		}	
	renderer.draw(sprite, shader);
}





