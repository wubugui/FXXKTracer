#pragma once
//ԭ�����ǲ�ʹ�ó���OpenGL��ʾ��һ���ֹ�������κ���������
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