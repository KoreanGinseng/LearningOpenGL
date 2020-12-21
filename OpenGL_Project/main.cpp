#define _CRT_SECURE_NO_WARNINGS

//! INCLUDE
#include <Windows.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <Commdlg.h>
#include <process.h>
#include <tchar.h>
#include <direct.h>

#include <string>
#include <codecvt>
#include <locale>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//! Load Static Library
#pragma comment( lib, "glew32.lib" )
#pragma comment( lib, "glfw3.lib" )
#pragma comment (lib, "OpenGL32.lib")

#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Comctl32.lib")

int gWidth  = 800;
int gHeight = 600;

#include <crtdbg.h>


using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;

namespace sip
{
	std::string to_string(std::wstring wstr)
	{
		return strconverter.to_bytes(wstr);
	}

	std::wstring to_wstring(std::string str)
	{
		return strconverter.from_bytes(str);
	}
}

void _PRINTLOG(const _TCHAR* fmt, ...)
{
	_TCHAR buf[512];
	va_list ap;
	va_start(ap, fmt);
	_vsntprintf(buf, 511, fmt, ap);
	buf[511] = 0;
	OutputDebugString(buf);
}

int main(int argc, char* argv[])
{
	//! デバッグフラグの設定
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//! glfwの初期化
	glfwInit();

	//! glfwウィンドウの生成
	GLFWwindow* window = glfwCreateWindow(gWidth, gHeight, "LearningOpenGL", nullptr, nullptr);

	//! glfwでコンテキストの作成
	glfwMakeContextCurrent(window);

	//! glewの初期化
	glewInit();

	const GLubyte* version = glGetString(GL_VERSION);
	const std::string str = (const char*)version;
	_PRINTLOG(L"GL version : %s\n", sip::to_wstring(str).c_str());

	//! メインループ
	while (!glfwWindowShouldClose(window))
	{
		//! ESCAPEキーが押されたらウィンドウを終了させる
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		//! 画面の色をクリア
		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//! バッファのスワップ
		glfwSwapBuffers(window);

		//! イベントキューの確認
		glfwPollEvents();
	}

	//! リソースの解放
	glfwTerminate();
	return 0;
}