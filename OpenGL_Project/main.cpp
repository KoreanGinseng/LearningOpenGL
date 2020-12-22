//! INCLUDE

#include "SipCommon.h"

#include <fstream>

#include <crtdbg.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//! Load Static Library
#pragma comment( lib, "glew32.lib" )
#pragma comment( lib, "glfw3.lib" )
#pragma comment (lib, "OpenGL32.lib")

int gWidth  = 800;
int gHeight = 600;

int main(int argc, char* argv[])
{
	//! �f�o�b�O�t���O�̐ݒ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SetCurrentDirectory("OpenGL_Project");

	//! glfw�̏�����
	glfwInit();

	//! glfw�E�B���h�E�̐���
	GLFWwindow* window = glfwCreateWindow(gWidth, gHeight, "LearningOpenGL", nullptr, nullptr);

	//! glfw�ŃR���e�L�X�g�̍쐬
	glfwMakeContextCurrent(window);

	//! glew�̏�����
	glewInit();

	//! GL Version �擾
	const GLubyte* version = glGetString(GL_VERSION);
	sip::SIP_PRINTLOG("GL version : %s\n", version);

	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 1.0f
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	std::ifstream ivs("vs.glsl");
	std::string vs((std::istreambuf_iterator<char>(ivs)), (std::istreambuf_iterator<char>()));
	const char* vsc = vs.c_str();

	std::ifstream ifs("fs.glsl");
	std::string fs((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	const char* fsc = fs.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsc, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsc, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	//! ���C�����[�v
	while (!glfwWindowShouldClose(window))
	{
		//! ESCAPE�L�[�������ꂽ��E�B���h�E���I��������
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		//! ��ʂ̐F���N���A
		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//! �o�b�t�@�̃X���b�v
		glfwSwapBuffers(window);

		//! �C�x���g�L���[�̊m�F
		glfwPollEvents();
	}

	//! ���\�[�X�̉��
	glfwTerminate();
	return 0;
}