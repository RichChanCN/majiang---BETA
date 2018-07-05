#ifndef __OPENGL_H__
#define __OPENGL_H__

#include <iostream>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL/SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include"Shader.h"
#include "Camera.h"
#include"Mesh.h"
#include"Model.h"


//回调代理类
#include"CallbackProxy.h"


using namespace std;

const GLuint WIDTH = 1280, HEIGHT = 720;

class OpenGL{
public:
	//在窗口显示;
	GLFWwindow* creatGLFWwindow();
	void showWindow(GLFWwindow* w);
	
	//移动相机
	void Do_Movement();

	void Do_Mouse_Rotate(GLFWwindow* window);

	//代理？
	static void setKeyBack(){
	}
	//鼠标相关回调函数
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode); 
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

private:

	// Camera
	static Camera  camera;
	static GLfloat lastX;
	static GLfloat lastY;
	static bool keys[1024];
	
	// Deltatime
	static GLfloat deltaTime;	// Time between current frame and last frame
	static GLfloat lastFrame; 	// Time of last frame

	static bool firstMouse;
	
	static bool draw;
	//// Camera
	//Camera  camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	//GLfloat lastX = WIDTH / 2.0;
	//GLfloat lastY = HEIGHT / 2.0;
	//bool    keys[1024];

	//// Deltatime
	//GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	//GLfloat lastFrame = 0.0f;  	// Time of last frame

	//bool firstMouse = true;
};

#endif