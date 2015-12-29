#pragma once
//原则，我们不使用除了OpenGL显示那一部分功能外的任何其他功能
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct GLFWContext
{
	GLFWwindow* window;

};

bool init_gl(GLFWwindow** window, const char* title, int width, int height);

bool create_window(const char* title, int width, int height);

void run();