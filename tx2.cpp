#include"Base.h"
#include"Shader.h"

unsigned int VBO = 0;
unsigned int VAO = 0;
unsigned int EBO = 0;
Shader _shader;

float vertices[] = {
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.7f, -0.9f, 0.0f,  1.0f, 0.0f, 0.0f,
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3,
	1, 2, 4,
};

void rend() {
	_shader.start();
	glBindVertexArray(VAO);	
	//draw
	//mode: these 3 vertex shape what
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	_shader.end();
}

void initModel() {
		//VBO: get buffer in GPU
	//1. get index of VBO
	//2. bind VBO(only in GPU before)
	//3. give memory, give data
	//4. let shader operate
	//5. activate

	//VAO: call CORE_PROFILE, so must use VAO to visual vertex, manager
	//a. get index of VBO
	//b. bind VAO


	//a
	glGenVertexArrays(1, &VAO);
	//b
	glBindVertexArray(VAO);

	//1-3
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//1
	glGenBuffers(1, &VBO);
	//2
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//3
	//gl_static_draw: let GPU know how to use "vertices"
	//MVP variation != dynamic, still static, not change "vertices"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//4
	// only 1 "0" in GPU, change VBO will flush all former VBO
	// so if draw more than 1 vertex, use VAO to record the real & of VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float)*3));
	//5
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	//release
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void initShader(const char* _vertexPath,const char* _fragPath) {
	_shader.initShader(_vertexPath, _fragPath);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	//if press space, close
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	//similar to conda creaete
	glfwInit();
	//windowhint(a,b): a=b;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Core", NULL, NULL);
	if (window == NULL) {
		std::cout << "window Failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	//bind "conda" to window
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "glad Failed" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);
	//if size change, call this
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	initModel();
	initShader("vertexShader.glsl", "fragmentShader.glsl");

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.99f, 0.79f, 0.99f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rend();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}