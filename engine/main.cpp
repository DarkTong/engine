#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GZJCommon.h"
#include "GZJRequire.h"
#include "GZJHeadFile.h"

#include "GZJTest.cpp"


using namespace GZJ_ENGINE;

GZJWindow win;
GZJTimePtr time = GZJTime::GetInstance();
GZJShaderManagerPtr shaderMgrPtr = GZJShaderManager::GetInstance();
GZJMeshManagerPtr meshMgrPtr;
GZJModelManagerPtr modelMgrPtr;
GZJModelPtr modelPtr;
GZJCamera mainCamera;
GZJEventSystemPtr eventSystemPtr = GZJEventSystem::GetInstance();
//GZJModelManagerPtr modelMgrPtr = MakeShared<GZJModelManager>(new GZJModelManager());
//GZJRenderStaticPtr renderStaitc = GZJRenderStatic::GetInstance();

DWORD next_game_tick = GetTickCount();// 返回当前的系统已经运行的毫秒数
int loops;
bool game_is_running = true;
bool is_test_normal_func = false;

// 用于临时操作
void Before_Draw();

void update_game();
void display_game();

// ------------- vertices ------------------------

float verticess[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// left  
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// right 
	0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top   
};
Vertex vertice;
//unsigned int indice[] = {
//	0, 1, 2,
//};
unsigned int VAO, VBO;
GZJShaderPtr shader;
GZJMeshPtr mesh;


int main() {
	//is_test_normal_func = true;
	//GZJTest test;
	//while (test.InputTransform()) {
	//	test.ShowTransform();
	//}

	// 若不是测试基本函数，则执行渲染
	if (!is_test_normal_func)
	{
		win.InitWindow();
		win.BuildWindow();
		shaderMgrPtr->StartUp();
		//meshMgrPtr = std::dynamic_pointer_cast<GZJMeshManager>((new GZJMeshManager)->GetSelf());
		modelMgrPtr = std::dynamic_pointer_cast<GZJModelManager>((new GZJModelManager())->GetSelf());
		//meshMgrPtr->StartUp();
		modelMgrPtr->StartUp();

		// 临时 ---------------- create shader program ----------
		// build and compile our shader program
		// ------------------------------------

		shader = std::dynamic_pointer_cast<GZJShader>(shaderMgrPtr->FindResByName("translate_1"));
		//mesh = std::dynamic_pointer_cast<GZJMesh>( meshMgrPtr->CreateRes("test1") );
		//Vertices vertices;
		//Vertex vertex1, vertex2, vertex3;
		//vertex1.position = Vector3(-0.5f, -0.5f, 0.0f);
		//vertex1.normal = Vector3(0.0f, 0.0f, 0.0f);

		//vertex2.position = Vector3(0.5f, -0.5f, 0.0f);
		//vertex2.normal = Vector3(0.0f, 0.0f, 0.0f);

		//vertex3.position = Vector3(0.0f, 0.5f, 0.0f);
		//vertex3.normal = Vector3(0.0f, 0.0f, 0.0f);

		//vertices.push_back(vertex1);
		//vertices.push_back(vertex2);
		//vertices.push_back(vertex3);

		//Indices indice({0,1,2,});
		//Textures tex;
		//mesh->Prepare(vertices, indice, tex);

		//mesh->Load();

		modelPtr = std::dynamic_pointer_cast<GZJModel>(modelMgrPtr->FindResByName("cube2"));

		modelPtr->Load();

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
		std::cout << "cnt:" << meshMgrPtr.use_count() << std::endl;
		//meshMgrPtr->ShutDown();
		modelMgrPtr->ShutDown();
	}

	return 0;
}

void update_game() {
	time->Update();
}

void display_game() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//shader->Use();
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3); 
	//mesh->Draw(shader);
	Before_Draw();

	Vector4x4 projection;
	float tmp = 1.0 * win.GetInt(Win_Width) / win.GetInt(Win_Height);
	projection = glm::perspective(glm::radians(45.0f), tmp, 0.1f, 100.0f);

	shader->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
	shader->SetMatrix(Shader_ViewToProjection, projection);

	modelPtr->SetShader(shader);
	modelPtr->Draw();

	//renderStaitc->Render();
}

void Before_Draw()
{
	mainCamera.SetVector3(CameraParam::Position, Vector3(0, 0, 10));
	mainCamera.SetVector3(CameraParam::Rotation, Vector3(0, 180, 0)); 
}

