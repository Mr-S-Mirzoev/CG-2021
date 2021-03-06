#include "gameplay/input_processing.h"
#include "gameplay/game.h"
#include <iostream>

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
    case GLFW_KEY_1:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;
    case GLFW_KEY_2:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;
    default:
        if (action == GLFW_PRESS)
            Input.keys[key] = true;
        else if (action == GLFW_RELEASE)
            Input.keys[key] = false;
	}
}

void processPlayerMovement(Game &game)
{
    bool toggled = false;

    if (Input.keys[GLFW_KEY_W]) {
        game.player_.ProcessInput(PlayerAction::UP);
        toggled = true;
    } else if (Input.keys[GLFW_KEY_S]) {
        game.player_.ProcessInput(PlayerAction::DOWN);
        toggled = true;
    }

    if (Input.keys[GLFW_KEY_A]) {
        game.player_.ProcessInput(PlayerAction::LEFT);
        toggled = true;
    } else if (Input.keys[GLFW_KEY_D]) {
        game.player_.ProcessInput(PlayerAction::RIGHT);
        toggled = true;
    }

    if (toggled)
        game.process_action();
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        Input.captureMouse = !Input.captureMouse;

    if (Input.captureMouse) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Input.capturedMouseJustNow = true;
    } else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
    if (Input.firstMouse) {
        Input.lastX = float(xpos);
        Input.lastY = float(ypos);
        Input.firstMouse = false;
    }

    GLfloat xoffset = float(xpos) - Input.lastX;
    GLfloat yoffset = Input.lastY - float(ypos);

    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    // ...
}
