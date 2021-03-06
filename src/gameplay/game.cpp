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
	lab_("./res/labitinth.txt"),
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
	std::cout << "Enter - apply an action to current room object" << std::endl;
	std::cout << "press ESC to exit" << std::endl;
}

void Game::loop() {
    Room roomA{Room::room_type::ROOM_TYPE_A};

    //game loop
	while (!glfwWindowShouldClose(window_)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    	glfwPollEvents();

		if (isEnterPressed())
			closest_object();
		processPlayerMovement(player_);
		roomA.DrawRoomOn(&screen_buffer_); // x grows from bottom to begining, y grows from left to right
		player_.Draw(screen_buffer_);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
	    glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screen_buffer_.Data()); GL_CHECK_ERRORS;

		glfwSwapBuffers(window_);
	}
}

GameObject* Game::closest_object() {
	auto& cur_room = lab_.get_current_room();
	auto  cur_pose = player_.get_current_pose();

	std::cout << "Hui" << std::endl;
	int x_min, y_min, x_max, y_max;
	cur_room.get_screen_pose(x_min, y_min, x_max, y_max);
	std::cout << "Pizda" << std::endl;

	cur_pose.x -= x_min + 8;
	cur_pose.y -= y_min + 8;

	auto x_cached = (cur_pose.x % 16);
	cur_pose.x = cur_pose.x - x_cached + (x_cached % 16 > 8 ? 16 : 0);

	auto y_cached = (cur_pose.y % 16);
	cur_pose.y = cur_pose.y - y_cached + (y_cached % 16 > 8 ? 16 : 0);

	auto &game_obj = cur_room.game_object_by_idxs({cur_pose.x / 16, cur_pose.y / 16});
	std::cout << game_obj.get_name() << std::endl;

	return &game_obj;
}

Game::~Game () {
    glfwTerminate();
}