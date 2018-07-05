#include"OpenGL.h"

//=====================================================================================================
//静态成员类外初始化
// Camera
Camera OpenGL::camera = Camera(glm::vec3(0.0f, 0.0f, 30.0f));
GLfloat OpenGL::lastX = WIDTH / 2.0;
GLfloat OpenGL::lastY = HEIGHT / 2.0;
bool OpenGL::keys[1024];
// Deltatime
GLfloat OpenGL::deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat OpenGL::lastFrame = 0.0f;  	// Time of last frame

bool OpenGL::firstMouse = true;
bool OpenGL::draw = false;
//=====================================================================================================

GLFWwindow* OpenGL::creatGLFWwindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "blood battle of Majiang!", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);


	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}

	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	return window;
}

void OpenGL::showWindow(GLFWwindow* w)
{
	Shader ourShader("vshader.glsl", "fshader.glsl");

	Model mj2("resource/mj/majiang.obj");
	Model mjz("resource/mjz/42.obj");
	

	while (!glfwWindowShouldClose(w))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		Do_Movement();
		//Do_Mouse_Rotate(w);
		// Clear the colorbuffer
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();   // <-- Don't forget this one!
		// Transformation matrices
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		
		// Draw the loaded model
		glm::mat4 model1;
		model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model1 = glm::scale(model1, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));
		mj2.Draw(ourShader);

		
		glm::mat4 model3;
		model3 = glm::translate(model3, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model3));
		mj2.Draw(ourShader);


		glfwSwapBuffers(w);
	}

}

// Moves/alters the camera positions based on user input
void OpenGL::Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void OpenGL::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		draw = true;
		
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		draw = false;

	}
}

void OpenGL::Do_Mouse_Rotate(GLFWwindow* window)
{
	double xpos, ypos;
	while (keys[GLFW_MOUSE_BUTTON_LEFT])
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		GLfloat xoffset = (xpos - lastX);
		GLfloat yoffset = (lastY - ypos);

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

 void OpenGL::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	 if (firstMouse)
	 {
		 lastX = xpos;
		 lastY = ypos;
		 firstMouse = false;
	 
	 }
		 GLfloat xoffset = (xpos - lastX)*1.5;
		 GLfloat yoffset = (lastY - ypos)*1.5;

		 lastX = xpos;
		 lastY = ypos;

		 camera.ProcessMouseMovement(xoffset, yoffset);


}

void OpenGL::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void OpenGL::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}