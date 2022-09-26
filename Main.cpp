#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

int fakemain() {
	//init lib before calls
	glfwInit();

	//settings, let glfw know we use opengl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5,-0.5 ,0.0,
		0.5,-0.5,0.0,
		0.0,0.5,0.0,
	};

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
	glViewport(0, 400, 800, 600);

	//create ver and frag shader into shaderprogram
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//vertex binded object
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//similar to "set color"
	glClearColor(1.0, 0.8, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//glxxx is like figure.xxx(),glfw is like plt.xxx()
	glfwSwapBuffers(window);

	//waiting for op
	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0, 0.8, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//release window resource
	glfwDestroyWindow(window);

	//release glfw resource
	glfwTerminate();
	return 0;
}
