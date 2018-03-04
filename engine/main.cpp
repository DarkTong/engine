#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GZJCommon.h"
#include "GZJRequire.h"
#include "GZJHeadFile.h"


using namespace GZJ_ENGINE;

GZJWindow win;
GZJTimePtr time = GZJTime::GetInstance();
//GZJRenderStaticPtr renderStaitc = GZJRenderStatic::GetInstance();

DWORD next_game_tick = GetTickCount();// 返回当前的系统已经运行的毫秒数
int loops;
bool game_is_running = true;

void update_game();
void display_game();

// ------------- vertices ------------------------

float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left  
	0.5f, -0.5f, 0.0f, // right 
	0.0f,  0.5f, 0.0f  // top   
};




int main() {
	win.InitWindow();
	win.BuildWindow();

	GZJShaderManagerPtr shaderMgrPtr = GZJShaderManagerPtr(new GZJShaderManager(true));
	//GZJShaderManagerPtr shaderMgrPtr = GZJShaderManager::GetInstance();

	//// 临时 ---------------- create shader program ----------
	//// build and compile our shader program
	//// ------------------------------------
	//// vertex shader
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//// check for shader compile errors
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	//// fragment shader
	//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//// check for shader compile errors
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	//// link shaders
	//int shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	//// check for linking errors
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	//}
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	//RenderUtil data = RenderUtil(shaderProgram, vertices);
	//renderStaitc->AddRenderData(data);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(win.GetWindow()) && game_is_running)
	{

		loops = 0;
		while (time->GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP)
		{
			update_game();
			next_game_tick += SKIP_TICKS;
			loops++;
		}
		display_game();
		


		win.Process();
	}
	//renderStaitc->ClearRenderDatas();
	shaderMgrPtr->DeleteMe();
	shaderMgrPtr.reset();
	win.Close();

	return 0;
}

void update_game() {
	time->Update();
}

void display_game() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//renderStaitc->Render();
}

