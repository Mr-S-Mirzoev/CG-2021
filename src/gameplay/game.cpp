#include "utilities/common.h"
#include "utilities/room.h"
#include "utilities/labirinth.h"
#include "utilities/matrix.h"
#include "utilities/exceptions.h"

#include "gameplay/input_processing.h"
#include "gameplay/game.h"

extern GLfloat deltaTime;
extern GLfloat lastFrame;

Game::Game(): 
	player_({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}), 
	lab_("./res/maps/labirinth.txt"),
	screen_buffer_(WINDOW_WIDTH, WINDOW_HEIGHT, 4) 
{	
    if(!glfwInit())
    	throw utilities::GLException("Game initialization failed");

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
	if (window_ == nullptr) {
		glfwTerminate();
		throw utilities::GLException("Failed to create GLFW window");
	}
	
	glfwMakeContextCurrent(window_); 

	glfwSetKeyCallback          (window_, OnKeyboardPressed);  
	glfwSetCursorPosCallback    (window_, OnMouseMove); 
  	glfwSetMouseButtonCallback  (window_, OnMouseButtonClicked);
	glfwSetScrollCallback       (window_, OnMouseScroll);
	
	initGL();

  	// Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  GL_CHECK_ERRORS;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;
}

void Game::initGL() const
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw utilities::GLException("Failed to initialize OpenGL context");

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	std::cout << "Controls:" << std::endl;
	std::cout << "press right mouse button to capture/release mouse cursor" << std::endl;
	std::cout << "W, A, S, D - movement" << std::endl;
	std::cout << "press ESC to exit" << std::endl;
}

void Game::loop() {
    //game loop
	while (!glfwWindowShouldClose(window_)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    	glfwPollEvents();

		processPlayerMovement(*this);
		lab_.get_current_room().DrawRoomOn(&screen_buffer_); // x grows from bottom to begining, y grows from left to right
		player_.Draw(screen_buffer_);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
	    glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screen_buffer_.Data()); GL_CHECK_ERRORS;

		glfwSwapBuffers(window_);
	}
}

std::pair <int, int> Game::get_pose_in_map_coords() {
	auto player_coords = player_.get_coords();
	player_coords.x += tileSize / 2;
	player_coords.y += tileSize / 2;
	std::cout << player_coords.x << " " << player_coords.y << std::endl;

	auto pt2 = lab_.get_current_room().get_mins();
	std::cout << "lab mins " << pt2.first << " " << pt2.second << std::endl;

	int delta_x = player_coords.x - tileSize * pt2.first;
	int delta_y = player_coords.y - tileSize * pt2.second;

	std::cout << "delta x y " << delta_x / tileSize << " " << delta_y / tileSize << std::endl;

	int object_i = (delta_x / tileSize) + 1;
	int object_j = (delta_y / tileSize) + 1;

	std::cout << "obj i j " << object_i << " " << object_j << std::endl;

	return {object_i, object_j};
}

std::vector<std::pair <int, int>> Game::get_poses_in_map_coords() {
	auto player_coords = player_.get_coords();
	//player_coords.x += tileSize / 2;
	//player_coords.y += tileSize / 2;
	std::cout << player_coords.x << " " << player_coords.y << std::endl;
	auto pt2 = lab_.get_current_room().get_mins();
	std::cout << "lab mins " << pt2.first << " " << pt2.second << std::endl;

	std::vector<std::pair <int, int>> result;
	const int dx[] = {0, 0, tileSize - 1, tileSize - 1};
	const int dy[] = {0, tileSize - 1, 0, tileSize - 1};
	for (int dId = 0; dId < 4; ++dId) {

		int delta_x = player_coords.x - tileSize * pt2.first  + dx[dId];
		int delta_y = player_coords.y - tileSize * pt2.second + dy[dId];

		std::cout << "dId: " << dId << std::endl;
		std::cout << "delta x y " << delta_x / tileSize << " " << delta_y / tileSize << std::endl;

		int object_i = (delta_x / tileSize);// + 1;
		int object_j = (delta_y / tileSize);// + 1;

		std::cout << "obj i j " << object_i << " " << object_j << std::endl;

		bool has = false;
		for (auto rs : result)
			if (rs.first == object_i && rs.second == object_j)
				has = true;
		if (!has)
			result.push_back({object_i, object_j});
	}
	return result;
}


void Game::process_action() {
	auto objects = get_poses_in_map_coords();
	auto object = get_pose_in_map_coords();

	auto sz = lab_.get_current_room().get_size();
	std::cout << "Process" << std::endl;
	for(auto obj : objects) {
		auto cur_tile = lab_.get_current_room().get_layout()[obj.second][obj.first];
		cur_tile->apply_action(*this);
		std::cout << cur_tile->get_name() << std::endl;
	}
}

int Game::get_direction() {
	std::cout << "Direct" << std::endl;
	auto object = get_pose_in_map_coords();

	std::cout << "Object: " << object.first << " " << object.second << std::endl;

	if (object.first == 0) {
		return mapping::GO_LEFT;
	} else if (object.first == lab_.get_current_room().get_size().first - 1) {
		return mapping::GO_RIGHT;
	}

	if (object.second == 0) {
		return mapping::GO_UP;
	} else {
		return mapping::GO_DOWN;
	}
}

Game::~Game () {
    glfwTerminate();
}