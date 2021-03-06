#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "gameplay/Player.h"

constexpr GLsizei WINDOW_WIDTH = 512, WINDOW_HEIGHT = 512;

struct InputState
{
    bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
    GLfloat lastX = 400, lastY = 300; //исходное положение мыши
    bool firstMouse = true;
    bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
    bool capturedMouseJustNow = false;
} static Input;

void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode);

void processPlayerMovement(Player &player);

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods);

void OnMouseMove(GLFWwindow* window, double xpos, double ypos);

bool isEnterPressed();

void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset);

#endif // IMAGE_PROCESSING_H