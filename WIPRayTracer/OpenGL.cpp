#include "stdio.h"
#include "OpenGL.h"

bool init_gl(GLFWwindow** window, const char* title, int width, int height)
{


	if (!glfwInit())
	{
		printf("glfwInit() failed!\n");
		getchar();
		//exit(0);
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	*window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(*window);
	//set all callbacks

	glewInit();

	return true;
}

bool create_window(const char* title, int width, int height)
{


	return true;
}

