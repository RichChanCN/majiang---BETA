#ifndef __SHOWMAJIANG_H__
#define __SHOWMAJIANG_H__

#define GLEW_STATIC  //静态链接的宏
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include<iostream>
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<windows.h>
#include <mmsystem.h>
#pragma  comment(lib,"WinMM.Lib")

#include"Shader.h"
#include "Camera.h"
#include"Mesh.h"
#include"Model.h"
#include "configure.h"

using namespace std;

typedef glm::vec4 point4;
typedef glm::vec4 color4;
typedef glm::vec3 point3;

const GLuint WIDTH = 800, HEIGHT = 800;



struct object{//物体结构
	int name;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
};

struct Light//光源结构
{   
	glm::vec4 position;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
};

struct Material//材质结构
{
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;
};


class OldOpenGL{
public:

	//加载OBJ文件的函数
	bool loadOBJ(
		const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
		);

	void vTop(object &o );

	//在窗口显示;
	GLFWwindow* creatGLFWwindow();
	void showWindow(GLFWwindow* w);



private:
	// Camera
	Camera  camera=Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	GLfloat lastX = WIDTH / 2.0;
	GLfloat lastY = HEIGHT / 2.0;
	bool    keys[1024];

	// Deltatime
	GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame
	
};


#endif