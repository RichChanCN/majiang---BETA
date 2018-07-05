#ifndef __SHOWMAJIANG_H__
#define __SHOWMAJIANG_H__

#define GLEW_STATIC  //��̬���ӵĺ�
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



struct object{//����ṹ
	int name;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
};

struct Light//��Դ�ṹ
{   
	glm::vec4 position;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
};

struct Material//���ʽṹ
{
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;
};


class OldOpenGL{
public:

	//����OBJ�ļ��ĺ���
	bool loadOBJ(
		const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
		);

	void vTop(object &o );

	//�ڴ�����ʾ;
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