
#include<Windows.h>
	#include<WinBase.h>
	#include<iostream>

#include <process.h>  
#include <stdlib.h>  
#include<stdio.h>

#include<map>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include"majiang.h"
#include"paidui.h"
#include"player.h"
#include"MyArray.h"
#include"play.h"
#include"configure.h"

#include"OpenGL.h"

#include <mmsystem.h>
#pragma comment(lib,"WinMM.Lib")

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
//=====================================================================================================
//初始化
// Camera
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 30.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

bool firstMouse = true;


GLFWwindow* creatWindow();
void Do_Movement();
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void Do_Mouse_Rotate(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//=====================================================================================================
glm::mat4 tempmat;
glm::mat4 scale_mat = glm::scale(tempmat, glm::vec3(0.2f, 0.2f, 0.2f));
//面朝下的牌的位置初始化
glm::mat4 down_mj_init = glm::translate(scale_mat, glm::vec3(0.0f, 0.0f, 11.5f));
//立着的牌的位置初始化
glm::mat4 li_mj_init = glm::translate(glm::rotate(scale_mat, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0)), glm::vec3(0.0f, -10.0f, 0.0f));//先绕X旋转再升起到桌面
//面朝上的牌的位置初始化
glm::mat4 up_mj_init = glm::translate(glm::rotate(scale_mat, glm::radians(180.0f), glm::vec3(1.0, 0.0, 0.0)), glm::vec3(0.0f, 0.0f, -11.5f));//先绕X旋转再升起到桌面

glm::mat4 paidui_mat[MAX_MAJIANG_NUM];
glm::mat4 shoupai_mat[4][MAX_MAJIANG_SHOU];
glm::mat4 zhuopai_mat[4][4][4];
glm::mat4 paichi_mat[4][MAX_MAJIANG_PAICHI];
glm::mat4 showshoupai_mat[4][MAX_MAJIANG_SHOU];

POINT chupaipoints[56];
POINT xuanzepoints[8];
void paiduiMatInit();
void shoupaiMatInit();
void zhuopaiMatInit();
void paichiMatInit();
void modelInit();
void initAll();
void fontsInit();
//unsigned __stdcall gameStart(LPVOID pM);
//void gameStart();
unsigned __stdcall  gameLoop(LPVOID pM);

void draw();
bool PtInAnyRect(POINT pCur, POINT pLT, POINT pLB, POINT pRB, POINT pRT);
int chooseChuPai(double x, double y);
int chooseYN(double x, double y);
bool gangPai_1(int *m, int who);
bool gangPai_2(const Majiang *m, int who);
//void showAll();
//=====================================================================================================
GLFWwindow* w = creatWindow();

Shader ourShader("vshader.glsl", "fshader.glsl");
Shader fontShader("fontsvshader.glsl", "fontsfshader.glsl");
Model models[40];
Model mj2("resource/mj/majiang.obj");
Model mjz_model("resource/mjz/42.obj");
Model sz_model("41.obj");
//====================================================================================================
//字体结构
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;

GLuint VAOf, VBOf;

void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
//=====================================================================================================
Play game;
HANDLE handle;
int choose = -1;
int dowhat = DONOT;
int yesorno = -1;
string mjInfo = "";
Majiang midshow(40);
int gamestate;
int winner = 0;
int gamespeed;
//=====================================================================================================

void showclick()
{
	RenderText(fontShader, "zhuangjia is " + to_string(game.zhuangjia), 25.0f, 680.0f, 0.8f, glm::vec3(0.5, 0.8f, 0.2f));
	RenderText(fontShader, "paidui has " + to_string(game.m_number) + " remains", 25.0f, 650.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

	RenderText(fontShader, "Game speed is " + to_string((2000 - gamespeed) / 100), 25.0f, 620.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
	RenderText(fontShader, "BGM switch is key S/P ", 25.0f, 540.0f, 0.5f, glm::vec3(0.5, 0.5f, 0.5f));
	RenderText(fontShader, "Game speed control Z/X", 25.0f, 510.0f, 0.5f, glm::vec3(0.5, 0.5f, 0.5f));
	RenderText(fontShader, "press right mouse button", 25.0f, 400.0f, 0.5f, glm::vec3(0.95, 0.65f, 0.7f));
	RenderText(fontShader, "you can have God viewport", 25.0f, 370.0f, 0.5f, glm::vec3(0.95, 0.65f, 0.7f));

	if (dowhat == PENGPAI)
	{
		RenderText(fontShader, "peng?", 900.0f, 480.0f, 1.2f, glm::vec3(0.2, 0.2f, 1.0f));
		RenderText(fontShader, "Yes!", 1000.0f, 400.0f, 0.9f, glm::vec3(0.2, 1.0f, 0.2f));
		RenderText(fontShader, "No!", 1150.0f, 400.0f, 0.9f, glm::vec3(1.0, 0.2f, 0.2f));
	}
	if (dowhat == CANGANG)
	{
		RenderText(fontShader, "gang?", 900.0f, 480.0f, 1.2f, glm::vec3(0.2, 0.2f, 1.0f));
		RenderText(fontShader, "Yes!", 1000.0f, 400.0f, 0.9f, glm::vec3(0.2, 1.0f, 0.2f));
		RenderText(fontShader, "No!", 1150.0f, 400.0f, 0.9f, glm::vec3(1.0, 0.2f, 0.2f));
	}
	if (dowhat == HUPAI)
	{
		RenderText(fontShader, "hu?", 900.0f, 480.0f, 1.2f, glm::vec3(0.2, 0.2f, 1.0f));
		RenderText(fontShader, "Yes!", 1000.0f, 400.0f, 0.9f, glm::vec3(0.2, 1.0f, 0.2f));
		RenderText(fontShader, "No!", 1150.0f, 400.0f, 0.9f, glm::vec3(1.0, 0.2f, 0.2f));
	}

	if (dowhat == GANGPAI)
	{
		RenderText(fontShader, "gang"+mjInfo+"?", 900.0f, 480.0f, 1.2f, glm::vec3(0.2, 0.2f, 1.0f));
		RenderText(fontShader, "Yes!", 1000.0f, 400.0f, 0.9f, glm::vec3(0.2, 1.0f, 0.2f));
		RenderText(fontShader, "No!", 1150.0f, 400.0f, 0.9f, glm::vec3(1.0, 0.2f, 0.2f));
	}
	if (gamestate == OVER)
	{
		RenderText(fontShader, "GAME OVER!", 340.0f, 560.0f, 2.0f, glm::vec3(1.0, 1.0f, 1.0f));
		if (winner == 1)
			RenderText(fontShader, "WINNER IS YOU~", 340.0f, 480.0f, 1.5f, glm::vec3(1.0, 0.9f, 0.0f));
		else if (winner > 0 && winner <5)
		{
			RenderText(fontShader, "WINNER IS PLAYER-" + to_string(winner), 320.0f, 480.0f, 1.2f, glm::vec3(1.0, 1.0f, 1.0f));
			RenderText(fontShader, "ni zhe ge cai ji, dian nao dou da bu guo !", 220.0f, 430.0f, 1.0f, glm::vec3(1.0, 0.0f, 0.0f));
		}
		else
			RenderText(fontShader, "LIU JU,TRY AGAIN!", 330.0f, 480.0f, 1.5f, glm::vec3(1.0, 0.0f, 0.0f));

	}
}

//=====================================================================================================
void play()
{
	initAll();
	gamespeed = 1000;
	gamestate = RUNNING;
	game.readyToGo();
	game.go_FirstStep();

	camera.setCameraPosition(0.0f, -23.1f, 10.4f);
	camera.setCameraFront(0.0f, 0.96f, -0.28f);
	camera.Up = glm::vec3(0.0f, 0.0f, 1.0f);

	handle = (HANDLE)_beginthreadex(NULL, 0, gameLoop, NULL, 0, NULL);

	PlaySound(TEXT("resource\\music\\bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	while (!glfwWindowShouldClose(w))
	{

		draw();
		showclick();

		glfwSwapBuffers(w);
	}
}
int main(){
	
	play();

	return 0;
}

GLFWwindow* creatWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Richer Majiang!", nullptr, nullptr);
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
	glfwSetMouseButtonCallback(window, mouse_button_callback);

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
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return window;
}


// Moves/alters the camera positions based on user input
void Do_Movement()
{
//	 Camera controls
	if (gamestate == OVER){
		if (keys[GLFW_KEY_W])
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (keys[GLFW_KEY_S])
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (keys[GLFW_KEY_A])
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (keys[GLFW_KEY_D])
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (keys[GLFW_KEY_Z]){
		if (gamespeed > 500)
			gamespeed -= 10;
	}
	if (keys[GLFW_KEY_X]){
		if (gamespeed < 1500)
			gamespeed += 10;
	}
	if (keys[GLFW_KEY_S]){
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}

	if (keys[GLFW_KEY_P]){
		PlaySound(TEXT("resource\\music\\bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	if (keys[GLFW_KEY_F1]){
		camera.Up = glm::vec3(0.0f, 0.0f, 1.0f);
		camera.setCameraPosition(0.0f, -23.1f, 10.4f);
		camera.setCameraFront(0.0f, 0.96f, -0.28f);
	}
	if (keys[GLFW_KEY_F2]){
		camera.Up = glm::vec3(0.0f, 0.0f, 1.0f);
		camera.setCameraPosition(-23.1f, 0.0f, 10.4f);
		camera.setCameraFront(0.96f, 0.0f, -0.28f);
	}
	if (keys[GLFW_KEY_F3]){
		camera.Up = glm::vec3(0.0f, 0.0f, 1.0f);
		camera.setCameraPosition(0.0f, 23.1f, 10.4f);
		camera.setCameraFront(0.0f, -0.96f, -0.28f);
	}
	if (keys[GLFW_KEY_F4]){
		camera.Up = glm::vec3(0.0f, 0.0f, 1.0f);
		camera.setCameraPosition(23.1f, 0.0f, 10.4f);
		camera.setCameraFront(-0.96f, 0.0f, -0.28f);
	}

	//if (gamestate == OVER)
	//{
	//	WaitForSingleObject(reinterpret_cast<HANDLE>(handle), INFINITE); //一直等到线程结束
	//	CloseHandle(reinterpret_cast<HANDLE>(handle));
	//	if (keys[GLFW_KEY_R])
	//	{
	//		initAll();
	//		gamespeed = 1000;
	//		gamestate = RUNNING;
	//		Play game = Play();
	//		game.readyToGo();
	//		game.go_FirstStep();

	//		camera.setCameraPosition(0.0f, -23.1f, 10.4f);
	//		camera.setCameraFront(0.0f, 0.96f, -0.28f);
	//		camera.Up = glm::vec3(0.0f, 0.0f, 1.0f);

	//		handle = (HANDLE)_beginthreadex(NULL, 0, gameLoop, NULL, 0, NULL);
	//	}
	//	
	//}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double x, y;
	int c;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && dowhat == CHUPAI)
	{
		glfwGetCursorPos(window, &x, &y);
//		cout << "(" << x << "," << y << ")" << endl;
		choose = chooseChuPai(x, y);
	
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && (dowhat == PENGPAI || dowhat == CANGANG || dowhat == HUPAI || dowhat == GANGPAI))
	{
		glfwGetCursorPos(window, &x, &y);
//		cout << "(" << x << "," << y << ")" << endl;
		yesorno = chooseYN(x, y);

	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
		camera.Up = glm::vec3(0.0f, 1.0f, 0.0f);
		camera.setCameraPosition(0.0f, 0.0f, 30.0f);
		camera.setCameraFront(0.0f, 0.0f, -1.0f);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE){
		camera.Up = glm::vec3(0.0f, 0.0f, 1.0f);
		camera.setCameraPosition(0.0f, -23.1f, 10.4f);
		camera.setCameraFront(0.0f, 0.96f, -0.28f);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
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
	if (key == GLFW_KEY_R && action == GLFW_PRESS && gamestate == OVER)
	{
//		play();
	}

}

void paiduiMatInit()
{
	//第一个牌堆的第一个起始位置
	glm::mat4 pd1_1 = glm::translate(down_mj_init, glm::vec3(37.0f, -40.3f, 3.0f));
	//第二个牌堆的第一个起始位置
	glm::mat4 temp_pd = glm::rotate(down_mj_init, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Z轴旋转
	glm::mat4 pd2_1 = glm::translate(temp_pd, glm::vec3(34.5f, -40.3f, 3.0f));
	//第三个牌堆的第一个起始位置
	temp_pd = glm::rotate(down_mj_init, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Z轴旋转
	glm::mat4 pd3_1 = glm::translate(temp_pd, glm::vec3(37.0f, -40.3f, 3.0f));
	//第三个牌堆的第一个起始位置
	temp_pd = glm::rotate(down_mj_init, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Z轴旋转
	glm::mat4 pd4_1 = glm::translate(temp_pd, glm::vec3(34.5f, -40.3f, 3.0f));

	int n = 0;
	glm::mat4 temp_mat = pd1_1;
	for (int i = 0; i < 14; ++i){
		paidui_mat[n] = temp_mat;
		temp_mat = glm::translate(temp_mat, glm::vec3(0.0f, 0.0f, -3.0f));
		n++;
		paidui_mat[n] = temp_mat;
		temp_mat = glm::translate(temp_mat, glm::vec3(-5.0f, 0.0f, 3.0f));
		n++;
	}

	temp_mat = pd2_1;
	for (int i = 0; i < 13; ++i){
		paidui_mat[n] = temp_mat;
		temp_mat = glm::translate(temp_mat, glm::vec3(0.0f, 0.0f, -3.0f));
		n++;
		paidui_mat[n] = temp_mat;
		temp_mat = glm::translate(temp_mat, glm::vec3(-5.0f, 0.0f, 3.0f));
		n++;
	}

	temp_mat = pd3_1;
	for (int i = 0; i < 14; ++i){
		paidui_mat[n] = temp_mat;
		temp_mat = glm::translate(temp_mat, glm::vec3(0.0f, 0.0f, -3.0f));
		n++;
		paidui_mat[n] = temp_mat;
		temp_mat = glm::translate(temp_mat, glm::vec3(-5.0f, 0.0f, 3.0f));
		n++;
	}

	temp_mat = pd4_1;
	for (int i = 0; i < 13; ++i){
		paidui_mat[n] = temp_mat;
		temp_mat = glm::translate(temp_mat, glm::vec3(0.0f, 0.0f, -3.0f));
		n++;
		paidui_mat[n] = temp_mat;
		temp_mat = glm::translate(temp_mat, glm::vec3(-5.0f, 0.0f, 3.0f));
		n++;
	}
}

void shoupaiMatInit()
{
	glm::mat4 sp[4];
	glm::vec3 loc = glm::vec3(-42.4f, 0.0f, -61.7f);
	//玩家1手牌的第一个起始位置
	sp[0] = glm::translate(li_mj_init, loc);

	//玩家2手牌的第一个起始位置
	glm::mat4 temp_sp = glm::rotate(li_mj_init, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));//先绕Y轴旋转
	sp[1] = glm::translate(temp_sp, loc);

	//玩家3手牌的第一个起始位置
	temp_sp = glm::rotate(li_mj_init, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));//先绕Y轴旋转
	sp[2] = glm::translate(temp_sp, loc);

	//玩家4手牌的第一个起始位置
	temp_sp = glm::rotate(li_mj_init, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));//先绕Y轴旋转
	sp[3] = glm::translate(temp_sp, loc);

	glm::mat4 temp_mat;
	for (int i = 0; i < 4; ++i){
		temp_mat = sp[i];
		for (int j = 0; j < MAX_MAJIANG_SHOU; ++j){
			shoupai_mat[i][j] = temp_mat;
			temp_mat = glm::translate(temp_mat, glm::vec3(5.2f, 0.0f, 0.0f));
		}
	}


	loc = glm::vec3(-42.4f, 60.0f, 0.0f);
	//玩家1手牌的第一个起始位置
	sp[0] = glm::translate(up_mj_init, loc);

	//玩家2手牌的第一个起始位置
	temp_sp = glm::rotate(up_mj_init, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	sp[1] = glm::translate(temp_sp, loc);

	//玩家3手牌的第一个起始位置
	temp_sp = glm::rotate(up_mj_init, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	sp[2] = glm::translate(temp_sp, loc);

	//玩家4手牌的第一个起始位置
	temp_sp = glm::rotate(up_mj_init, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	sp[3] = glm::translate(temp_sp, loc);
	for (int i = 0; i < 4; ++i)
	{
		temp_mat = sp[i];
		for (int j = 0; j < MAX_MAJIANG_SHOU; ++j)
		{
			showshoupai_mat[i][j] = temp_mat;
			temp_mat = glm::translate(temp_mat, glm::vec3(5.2f, 0.0f, 0.0f));
		}
	}
}

void zhuopaiMatInit()
{
	glm::mat4 zp[4];
	glm::vec3 loc = glm::vec3(32.6f, 74.0f, 0.0f);
	//玩家1桌角第一张牌位置
	zp[0] = glm::translate(up_mj_init, loc);

	//玩家2桌角第一张牌位置
	glm::mat4 temp_sp = glm::rotate(up_mj_init, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	zp[1] = glm::translate(temp_sp, loc);

	//玩家3桌角第一张牌位置
	temp_sp = glm::rotate(up_mj_init, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	zp[2] = glm::translate(temp_sp, loc);

	//玩家4桌角第一张牌位置
	temp_sp = glm::rotate(up_mj_init, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	zp[3] = glm::translate(temp_sp, loc);

	glm::mat4 temp_mat;
	for (int i = 0; i < 4; ++i){
		temp_mat = zp[i];
		for (int j = 0; j < 4; ++j){
			for (int k = 0; k < 4; ++k){
				zhuopai_mat[i][j][k] = temp_mat;
				temp_mat = glm::translate(temp_mat, glm::vec3(5.0f, 0.0f, 0.0f));
			}
			temp_mat = glm::translate(temp_mat, glm::vec3(-20.0f, -6.0f, 0.0f));
		}
	}
}

void paichiMatInit()
{

	glm::mat4 pc[4];
	glm::vec3 loc = glm::vec3(-22.9f, 26.2f, 0.0f);
	//玩家1的牌池第一张
	pc[0] = glm::translate(up_mj_init, loc);

	//玩家2的牌池第一张
	glm::mat4 temp_pc = glm::rotate(up_mj_init, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	pc[1] = glm::translate(temp_pc, loc);

	//玩家3的牌池第一张
	temp_pc = glm::rotate(up_mj_init, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	pc[2] = glm::translate(temp_pc, loc);

	//玩家4的牌池第一张
	temp_pc = glm::rotate(up_mj_init, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));//先绕Y轴旋转
	pc[3] = glm::translate(temp_pc, loc);

	glm::mat4 temp_mat;
	for (int i = 0; i < 4; ++i){
		temp_mat = pc[i];
		for (int j = 0; j < MAX_MAJIANG_PAICHI; ++j){
			paichi_mat[i][j] = temp_mat;
			temp_mat = glm::translate(temp_mat, glm::vec3(5.0f, 0.0f, 0.0f));
			if (j == 8)
				temp_mat = glm::translate(pc[i], glm::vec3(0.0f, 6.0f, 0.0f));
			if (j == 17)
				temp_mat = glm::translate(pc[i], glm::vec3(0.0f, 12.0f, 0.0f));
		}
	}
}

void modelInit()
{
	int n = 0;
	for (int i = 1; i < 4; ++i)//类型循环
	{
		for (int j = 1; j < 10; ++j)//数值循环
		{
			models[i * 10 + j] = Model(i * 10 + j);
		}
	}
}

void pointInit()
{
			chupaipoints[0].x=161;chupaipoints[0].y= 574;
			chupaipoints[1].x=172;chupaipoints[1].y= 625;
			chupaipoints[2].x=221;chupaipoints[2].y= 623;
			chupaipoints[3].x=211;chupaipoints[3].y= 574;
			chupaipoints[4].x=216;chupaipoints[4].y= 575;
			chupaipoints[5].x=227;chupaipoints[5].y= 626;
			chupaipoints[6].x=277;chupaipoints[6].y= 625;
			chupaipoints[7].x=267;chupaipoints[7].y= 574;
			chupaipoints[8].x=271;chupaipoints[8].y= 575;
			chupaipoints[9].x=281;chupaipoints[9].y= 624;
			chupaipoints[10].x=328;chupaipoints[10].y= 623;
			chupaipoints[11].x=322;chupaipoints[11].y= 575;
			chupaipoints[12].x=328;chupaipoints[12].y= 575;
			chupaipoints[13].x=335;chupaipoints[13].y= 624;
			chupaipoints[14].x=385;chupaipoints[14].y= 625;
			chupaipoints[15].x=378;chupaipoints[15].y= 576;
			chupaipoints[16].x=384;chupaipoints[16].y= 574;
			chupaipoints[17].x=390;chupaipoints[17].y= 625;
			chupaipoints[18].x=438;chupaipoints[18].y= 624;
			chupaipoints[19].x=432;chupaipoints[19].y= 575;
			chupaipoints[20].x=439;chupaipoints[20].y= 573;
			chupaipoints[21].x=445;chupaipoints[21].y= 624;
			chupaipoints[22].x=493;chupaipoints[22].y= 626;
			chupaipoints[23].x=490;chupaipoints[23].y= 575;
			chupaipoints[24].x=495;chupaipoints[24].y= 574;
			chupaipoints[25].x=499;chupaipoints[25].y= 625;
			chupaipoints[26].x=548;chupaipoints[26].y= 626;
			chupaipoints[27].x=544;chupaipoints[27].y= 575;
			chupaipoints[28].x=552;chupaipoints[28].y= 575;
			chupaipoints[29].x=553;chupaipoints[29].y= 623;
			chupaipoints[30].x=600;chupaipoints[30].y= 624;
			chupaipoints[31].x=602;chupaipoints[31].y= 574;
			chupaipoints[32].x=606;chupaipoints[32].y= 576;
			chupaipoints[33].x=607;chupaipoints[33].y= 623;
			chupaipoints[34].x=655;chupaipoints[34].y= 625;
			chupaipoints[35].x=655;chupaipoints[35].y= 575;
			chupaipoints[36].x=661;chupaipoints[36].y= 575;
			chupaipoints[37].x=661;chupaipoints[37].y= 624;
			chupaipoints[38].x=710;chupaipoints[38].y= 624;
			chupaipoints[39].x=712;chupaipoints[39].y= 574;
			chupaipoints[40].x=717;chupaipoints[40].y= 575;
			chupaipoints[41].x=717;chupaipoints[41].y= 625;
			chupaipoints[42].x=764;chupaipoints[42].y= 623;
			chupaipoints[43].x=767;chupaipoints[43].y= 574;
			chupaipoints[44].x=774;chupaipoints[44].y= 575;
			chupaipoints[45].x=770;chupaipoints[45].y= 624;
			chupaipoints[46].x=819;chupaipoints[46].y= 625;
			chupaipoints[47].x=823;chupaipoints[47].y= 576;
			chupaipoints[48].x=828;chupaipoints[48].y= 574;
			chupaipoints[49].x=824;chupaipoints[49].y= 623;
			chupaipoints[50].x=873;chupaipoints[50].y= 624;
			chupaipoints[51].x=877;chupaipoints[51].y= 575;
			chupaipoints[52].x=883;chupaipoints[52].y= 574;
			chupaipoints[53].x=879;chupaipoints[53].y= 624;
			chupaipoints[54].x=929;chupaipoints[54].y= 625;
			chupaipoints[55].x=929;chupaipoints[55].y= 576;

			
			xuanzepoints[0].x = 1130; xuanzepoints[0].y = 270;
			xuanzepoints[1].x = 1130; xuanzepoints[1].y = 340;
			xuanzepoints[2].x = 1230; xuanzepoints[2].y = 340;
			xuanzepoints[3].x = 1230; xuanzepoints[3].y = 270;
			xuanzepoints[4].x = 1000; xuanzepoints[4].y = 270;
			xuanzepoints[5].x = 1000; xuanzepoints[5].y = 340;
			xuanzepoints[6].x = 1100; xuanzepoints[6].y = 340;
			xuanzepoints[7].x = 1100; xuanzepoints[7].y = 270;
}

void fontsInit()
{

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
	fontShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(fontShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//加载字体
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "resource/fonts/arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	//设置字体大小
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// Configure VAO/VBO for texture quads
	glGenVertexArrays(2, &VAOf);
	glGenBuffers(2, &VBOf);
	glBindVertexArray(VAOf);
	glBindBuffer(GL_ARRAY_BUFFER, VBOf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void initAll(){
	modelInit();
	pointInit();
	paiduiMatInit();
	shoupaiMatInit();
	zhuopaiMatInit();
	paichiMatInit();
	fontsInit();
}

//void showAll()
//{
//	glm::mat4 paidui_model;
//	for (int i = 0; i < MAX_MAJIANG_NUM; ++i){
//		paidui_model = paidui_mat[i];
//		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(paidui_model));
//		mj2.Draw(ourShader);
//	}
//	glm::mat4 shoupai_model;
//	for (int i = 0; i < 4; ++i){
//		for (int j = 0; j < MAX_MAJIANG_SHOU; ++j){
//			shoupai_model = shoupai_mat[i][j];
//			glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(shoupai_model));
//			mj2.Draw(ourShader);
//		}
//	}
//	glm::mat4 zhuopai_model;
//	for (int i = 0; i < 4; ++i){
//		for (int j = 0; j < 4; ++j){
//			for (int k = 0; k < 4; ++k){
//				zhuopai_model = zhuopai_mat[i][j][k];
//				glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(zhuopai_model));
//				mj2.Draw(ourShader);
//			}
//		}
//	}
//	glm::mat4 paichi_model;
//	for (int i = 0; i < 4; ++i){
//		for (int j = 0; j < MAX_MAJIANG_PAICHI; ++j){
//			paichi_model = paichi_mat[i][j];
//			glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(paichi_model));
//			mj2.Draw(ourShader);
//		}
//	}
//}

void draw()
{
	// Set frame time
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Check and call events
	glfwPollEvents();
	Do_Movement();

	// Clear the colorbuffer
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	ourShader.Use();   // <-- Don't forget this one!
	// Transformation matrices
	glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));



	int value;

	value = midshow.getTypeValue();
	if (value != EMPTY)
	{
		tempmat = li_mj_init;
		tempmat = glm::scale(tempmat, glm::vec3(3.0f, 3.0f, 3.0f));
		tempmat = glm::translate(tempmat, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(tempmat));
		models[value].Draw(ourShader);
	}

	for (int i = 0; i < MAX_MAJIANG_NUM; ++i)
	{
		value = game.paidui.getAll()[i].getTypeValue();
		if (value != EMPTY)
		{
			tempmat = paidui_mat[i];
			glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(tempmat));
			models[value].Draw(ourShader);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < MAX_MAJIANG_PAICHI; ++j)
		{
			value = game.wanjia[i + 1].getPaichi()[j].getTypeValue();
			if (value != EMPTY)
			{
				tempmat = paichi_mat[i][j];
				glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(tempmat));
				models[value].Draw(ourShader);
			}
		}
	}

	if (gamestate == OVER)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < MAX_MAJIANG_SHOU; ++j)
			{
				value = game.wanjia[i + 1].getShoupai()[j].getTypeValue();
				if (value != EMPTY)
				{
					tempmat = showshoupai_mat[i][j];
					glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(tempmat));
					models[value].Draw(ourShader);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < MAX_MAJIANG_SHOU; ++j)
			{
				value = game.wanjia[i + 1].getShoupai()[j].getTypeValue();
				if (value != EMPTY)
				{
					tempmat = shoupai_mat[i][j];
					glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(tempmat));
					models[value].Draw(ourShader);
				}
			}
		}
	}


	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < MAJIANG_ZHUOJIAO_COLS; ++j)
		{
			for (int k = 0; k < MAJIANG_ZHUOJIAO_ROWS; ++k)
			{
				value = game.wanjia[i + 1].getZhuopai(j,k).getTypeValue();
				if (value != EMPTY)
				{
					tempmat = zhuopai_mat[i][j][k];
					glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(tempmat));
					models[value].Draw(ourShader);
				}
			}
		}
	}
	
	glm::mat4 mjz_mat;
	mjz_mat = glm::translate(scale_mat, glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(mjz_mat));
	mjz_model.Draw(ourShader);

	//glm::mat4 sz_mat;
	//sz_mat = glm::translate(scale_mat, glm::vec3(0.0f, 0.0f, 10.0f));
	//glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(sz_mat));
	//sz_model.Draw(ourShader);

//	glfwSwapBuffers(w);
}

unsigned __stdcall gameLoop(LPVOID pM)
{
	int who;//临时储存who
	int current = game.zhuangjia;
	bool zhua = true;

	while (game.getHuplayernum() > MAJIANG_MOSHI && game.m_number > 0)
	{
		while (!game.wanjia[current].getHupai())
		{
			if (zhua)
			{
				
				game.giveOnePai(player(current));
				
				if (game.wanjia[current].canHu())//自摸判断
				{
					if (current == PLAYER)
					{
						dowhat = HUPAI;
						while (yesorno < 0 || yesorno > 1)
						{
							Sleep(DELAY);
						}
						if (yesorno)
						{
							winner = PLAYER;
							game.wanjia[current].huPai(yesorno);
							yesorno = -1;
							dowhat = JIANCE;
							current = current - 1 > 0 ? current - 1 : 4;
							zhua = true;
							// continue;
							break;
						}
						else
						{
							yesorno = -1;
							dowhat = JIANCE;
						}
					}
					else 
					{
						winner = current;
						game.wanjia[current].huPai();
						current = current - 1 > 0 ? current - 1 : 4;
						zhua = true;
						// continue;
						break;
					}
				}


				if (gangPai_1(game.wanjia[current].canGang_1(),current))
				{
					zhua = true;
					continue;
				}

				if (gangPai_2(game.wanjia[current].canGang_2(),current))
				{
					zhua = true;
					continue;
				}

			}

			
			if (current == PLAYER)
			{
				dowhat = CHUPAI;
				while (choose < 0 || choose > game.wanjia[current].getPaiNum() - 1)
				{
					Sleep(DELAY);
				}
				game.chupai(player(current), choose);
				choose = -1;
				dowhat = JIANCE;
			}
			else
			{
				Sleep(gamespeed);
				game.chupai(player(current));
			}

			midshow = game.keypai;

			who = game.whoCanHu(game.keypai);

			if (who && who != current)//吃胡判断
			{
				if (who == PLAYER)
				{
					dowhat = HUPAI;
					while (yesorno < 0 || yesorno > 1)
					{
						Sleep(DELAY);
					}
					if (yesorno)
					{
						winner = PLAYER;
						game.wanjia[who].huPai(game.keypai, yesorno);
						yesorno = -1;
						dowhat = JIANCE;
						current = who - 1 > 0 ? who - 1 : 4;
						zhua = true;
						//coutine;
						break;
					}
					else
					{
						yesorno = -1;
						dowhat = JIANCE;
					}
				}
				else
				{
					winner = who;
					game.wanjia[who].huPai();
					current = current - 1 > 0 ? current - 1 : 4;
					zhua = true;
					// continue;
					break;
				}

			}
			who = game.whoCanPeng(game.keypai);

			if (who && who != current )//碰牌判断
			{

				if (who == PLAYER)
				{
					dowhat = PENGPAI;
					while (yesorno < 0 || yesorno > 1)
					{
						Sleep(DELAY);
					}
					if (yesorno)
					{
						game.wanjia[who].pengPai(game.keypai, yesorno);
						yesorno = -1;
						dowhat = JIANCE;
						current = who;
						zhua = false;
						continue;
					}
					else
					{
						yesorno = -1;
						dowhat = JIANCE;
					}
				}
				else
				{
					Sleep(gamespeed/2);
					game.wanjia[who].pengPai(game.keypai);
					current = who;
					zhua = false;
					continue;
				}
			}

			who = game.whoCanGang(game.keypai);

			if (who && who != 5 && who != current)//杠牌判断
			{

				if (who == PLAYER)
				{
					dowhat = GANGPAI;
					while (yesorno < 0 || yesorno > 1)
					{
						Sleep(DELAY);
					}
					if (yesorno)
					{
						game.wanjia[who].gangPai_Shou(game.keypai, yesorno);
						yesorno = -1;
						dowhat = JIANCE;
						current = who;
						zhua = true;
						continue;
					}
					else
					{
						yesorno = -1;
						dowhat = JIANCE;
					}
				}
				else
				{
					Sleep(gamespeed / 2);
					game.wanjia[who].gangPai_Shou(game.keypai);
					current = who;
					zhua = true;
					continue;
				}
			}

			game.wanjia[current].addPaichi(game.keypai);

			zhua = true;
			current = current - 1 > 0 ? current - 1 : 4;
			Sleep(gamespeed/2);
			break;
		}

	}

	gamestate = OVER;
	return 0;
}

bool PtInAnyRect(POINT pCur, POINT pLT, POINT pLB, POINT pRB, POINT pRT)
{
	//任意四边形有4个顶点  
	int nCount = 4;
	POINT RectPoints[4] = { pLT, pLB, pRB, pRT };
	int nCross = 0;
	for (int i = 0; i < nCount; i++)
	{
		//依次取相邻的两个点  
		POINT pStart = RectPoints[i];
		POINT pEnd = RectPoints[(i + 1) % nCount];

		//相邻的两个点是平行于x轴的，肯定不相交，忽略  
		if (pStart.y == pEnd.y)
			continue;

		//交点在pStart,pEnd的延长线上，pCur肯定不会与pStart.pEnd相交，忽略  
		if (pCur.y < min(pStart.y, pEnd.y) || pCur.y > max(pStart.y, pEnd.y))
			continue;

		//求当前点和x轴的平行线与pStart,pEnd直线的交点的x坐标  
		double x = (double)(pCur.y - pStart.y) * (double)(pEnd.x - pStart.x) / (double)(pEnd.y - pStart.y) + pStart.x;

		//若x坐标大于当前点的坐标，则有交点  
		if (x > pCur.x)
			nCross++;
	}

	// 单边交点为偶数，点在多边形之外   
	return (nCross % 2 == 1);
}

int chooseChuPai(double x,double y)
{

	POINT p;
	p.x = x;
	p.y = y;

	for (int i = 0; i < 14; i++)
	{
		if (PtInAnyRect(p, chupaipoints[4 * i], chupaipoints[4 * i + 1], chupaipoints[4 * i + 2], chupaipoints[4 * i + 3]))
			return i;
	}

	return -1;
}

int chooseYN(double x, double y)
{

	//	glfwGetCursorPos(w, &x, &y);

	POINT p;
	p.x = x;
	p.y = y;

	for (int i = 0; i < 2; i++)
	{
		if (PtInAnyRect(p, xuanzepoints[4 * i], xuanzepoints[4 * i + 1], xuanzepoints[4 * i + 2], xuanzepoints[4 * i + 3]))
			return i;
	}

	return -1;
}

void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// Activate corresponding render state	
	shader.Use();
	glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAOf);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },

			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBOf);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool gangPai_1(int *m ,int who)
{
	int temp;

	if (m[0] + m[1] + m[2] + m[3] == 0)
		return false;

	bool gang;

	if (MAJIANG_AI&&who != PLAYER)
	{
		gang = true;
	}
	else
	{
		dowhat = CANGANG;
		while (yesorno < 0 || yesorno > 1)
		{
			Sleep(DELAY);
		}
		gang = yesorno;
		yesorno = -1;
		dowhat = JIANCE;
	}

	if (gang){

		int n = 0;

		while (n < 4)
		{
			if (m[n] == 0)
				continue;

			if (MAJIANG_AI&&who != PLAYER)
			{
				gang = true;
			}
			else
			{
				temp = game.wanjia[who].getZhuopai(m[n],0).getTypeValue();
				switch (temp / 10)
				{
				case 1:
					mjInfo = to_string(temp % 10) + "wan";
					break;
				case 2:
					mjInfo = to_string(temp % 20) + "tong";
					break;
				case 3:
					mjInfo = to_string(temp % 30) + "tiao";
					break;
				}

				dowhat = GANGPAI;
				while (yesorno < 0 || yesorno > 1)
				{
					Sleep(DELAY);
				}
				gang = yesorno;
				yesorno = -1;
				dowhat = JIANCE;
			}
			
			if (gang)
			{
				game.wanjia[who].p_fanshu = game.wanjia[who].p_fanshu * 2;

				Majiang mjtemp = game.wanjia[who].zhuopai[m[n]][0];

				game.wanjia[who].zhuopai[m[n]][3].mjVTcopy(mjtemp);

				for (int i = 0; i < game.wanjia[who].getPaiNum(); ++i)
				{
					if (game.wanjia[who].getShoupai()[i].mjVTequal(mjtemp)){
						game.wanjia[who].getShoupai()[i].setTypeValue(EMPTY);
					}
				}
				if (LIPAI_SWITCH)
					game.wanjia[who].liPai();
				delete[]m;

				return true;
			}

			n++;
		}

	}
	delete[]m;
	return false;
}

bool gangPai_2(const Majiang * m , int who)
{
	if (m[0].getTypeValue() == EMPTY && m[1].getTypeValue() == EMPTY && m[2].getTypeValue() == EMPTY)
		return false;

	bool gang;
	int temp;

	if (MAJIANG_AI&&who != PLAYER)
	{
		gang = true;
	}
	else
	{
		dowhat = CANGANG;
		while (yesorno < 0 || yesorno > 1)
		{
			Sleep(DELAY);
		}
		gang = yesorno;
		yesorno = -1;
		dowhat = JIANCE;
	}

	if (gang){

		int n = 0;

		while (n < 3)
		{
			if (m[n].getTypeValue() == EMPTY)
				continue;

			if (MAJIANG_AI && who != PLAYER)
			{
				gang = true;
			}
			else
			{
				temp = m[n].getTypeValue();
				switch (temp / 10)
				{
				case 1:
					mjInfo = to_string(temp % 10) + "wan";
					break;
				case 2:
					mjInfo = to_string(temp % 20) + "tong";
					break;
				case 3:
					mjInfo = to_string(temp % 30) + "tiao";
					break;
				}

				dowhat = GANGPAI;
				while (yesorno < 0 || yesorno > 1)
				{
					Sleep(DELAY);
				}
				gang = yesorno;
				yesorno = -1;
				dowhat = JIANCE;
			}

			if (gang)
			{
				game.wanjia[who].p_fanshu = game.wanjia[who].p_fanshu * 2;

				int index = game.wanjia[who].getZJcols();
				int num = 0;
				for (int i = 0; i < MAX_MAJIANG_SHOU; ++i){
					if (game.wanjia[who].getShoupai()[i].mjVTequal(m[n]) && num < 4){
						game.wanjia[who].getShoupai()[i].setTypeValue(EMPTY);
						num++;
					}
				}

				for (int i = 0; i < 4; ++i){
					game.wanjia[who].zhuopai[index][i].setTypeValue(m[n].getTypeValue());
				}

				if (LIPAI_SWITCH)
					game.wanjia[who].liPai();

				//delete[]m;

				return true;
			}

			n++;
		}
	}


	return false;
}