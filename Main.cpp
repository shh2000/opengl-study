#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	//init lib before calls
	glfwInit();
	
	//settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create a window
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "OPENGL", NULL, NULL);
	//check if create successfully
	if (window == NULL) {
		glfwTerminate();
		std::cout << "Failed" << std::endl;
		return -1;
	}

	//about settings and thread?
	glfwMakeContextCurrent(window);

	//init glad before calls
	gladLoadGL();

	//determine subwindow
	glViewport(0,0,1920,1080);

	//similar to "set color"
	glClearColor(0.9, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnd();

	//glxxx is like figure.xxx(),glfw is like plt.xxx()
	glfwSwapBuffers(window);

	//waiting for op
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	//release window resource
	glfwDestroyWindow(window);

	//release glfw resource
	glfwTerminate();
	return 0;
}
