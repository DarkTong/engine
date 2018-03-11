#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GZJCommon.h"
#include "GZJRequire.h"
#include "GZJHeadFile.h"


using namespace GZJ_ENGINE;

GZJWindow win;
GZJTimePtr time = GZJTime::GetInstance();
GZJShaderManagerPtr shaderMgrPtr = GZJShaderManager::GetInstance();
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
unsigned int VAO, VBO;
GZJShaderPtr shader;


int main() {
	win.InitWindow();
	win.BuildWindow();
	shaderMgrPtr->StartUp();

	// 临时 ---------------- create shader program ----------
	// build and compile our shader program
	// ------------------------------------

	shader = std::dynamic_pointer_cast<GZJShader>(shaderMgrPtr->FindResByName("easy_1"));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	win.Close();
	std::cout << shader.use_count() << std::endl;
	shaderMgrPtr->ShutDown();

	return 0;
}

void update_game() {
	time->Update();
}

void display_game() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3); 

	//renderStaitc->Render();
}

