#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GZJCommon.h"
#include "GZJRequire.h"
#include "GZJHeadFile.h"

#include "GZJTest.cpp"


using namespace GZJ_ENGINE;

GZJWindowPtr win = GZJWindow::GetInstance();
GZJTimePtr gzjTime = GZJTime::GetInstance();
GZJLightManagerPtr lightMgrPtr = GZJLightManager::GetInstance();
GZJResourceLoadPtr resLoadPtr = GZJResourceLoad::GetInstance();
GZJShaderManagerPtr shaderMgrPtr = GZJShaderManager::GetInstance();
GZJModelManagerPtr modelMgrPtr = GZJModelManager::GetInstance();

GZJModelPtr modelPtr1;
GZJModelPtr modelPtr2;
const int NUM_CUBE = 10;
GZJModelPtr cubesModel[10];
GZJModelPtr parallelLightModel;
GZJModelPtr pointLightModel;
GZJModelPtr spotLightModel;
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
// 设置shader的一些属性
void InitShader();

void update_game();
void display_game();
// 键盘按键回调
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// 鼠标按键
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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
GZJShaderPtr shader1, shader2;
GZJShaderPtr parallelLS, pointLS, spotLS, normalS;
GZJLightPtr parallelLightPtr, pointLightPtr, spotLightPtr;


int main() {
	//is_test_normal_func = true;
	//GZJTest test;
	//while (test.InputTransform()) {
	//	test.ShowTransform();
	//}

	// 若不是测试基本函数，则执行渲染
	if (!is_test_normal_func)
	{
		win->InitWindow();
		win->BuildWindow();
		glfwSetKeyCallback(win->GetWindow(), key_callback);
		glfwSetMouseButtonCallback(win->GetWindow(), mouse_button_callback);

		resLoadPtr->StartUp();
		//eventSystemPtr->StartUp();
		lightMgrPtr->StartUp();
		shaderMgrPtr->StartUp();
		//meshMgrPtr = std::dynamic_pointer_cast<GZJMeshManager>((new GZJMeshManager)->GetSelf());
		//meshMgrPtr->StartUp();
		modelMgrPtr->StartUp();

		// 读取全局光照（临时）（使用写时复制）
		lightMgrPtr->GetSceneLightMap(1);

		// 临时获取平行光，用于测试
		auto it = lightMgrPtr->GetSceneLightMap(1).find(1);
		parallelLightPtr = it->second;
		it = lightMgrPtr->GetSceneLightMap(1).find(2);
		pointLightPtr = it->second;
		it = lightMgrPtr->GetSceneLightMap(1).find(3);
		spotLightPtr = it->second;

		// 临时 ---------------- create shader program ----------
		// build and compile our shader program
		// ------------------------------------
		mainCamera.SetVector3(CameraParam::Position, Vector3(0, 0, -10));
		mainCamera.moveCmp->moveSpeed = .007f;
		mainCamera.moveCmp->pitchSpeed = .02f;
		mainCamera.moveCmp->yawSpeed = .02f;
		//mainCamera.transform.SetVector3(Rotation, Vector3(0, 0, 180));
		shader1 = std::static_pointer_cast<GZJShader>
			(shaderMgrPtr->CreateRes("whiteLight_1"));
		parallelLS = std::static_pointer_cast<GZJShader>
			(shaderMgrPtr->CreateRes("parallel_light"));
		pointLS = std::static_pointer_cast<GZJShader>
			(shaderMgrPtr->CreateRes("point_light"));
		spotLS = std::static_pointer_cast<GZJShader>
			(shaderMgrPtr->CreateRes("spot_light"));
		normalS = std::static_pointer_cast<GZJShader>
			(shaderMgrPtr->CreateRes("normal"));

		shader1->Prepare();
		shader1->SyncLoad();
		parallelLS->Prepare();
		parallelLS->SyncLoad();
		pointLS->Prepare();
		pointLS->SyncLoad();
		spotLS->Prepare();
		spotLS->SyncLoad();
		normalS->Prepare();
		normalS->SyncLoad();


		modelPtr1 = std::static_pointer_cast<GZJModel>
			(modelMgrPtr->CreateRes("cube1"));
		modelPtr1->SyncLoad();
		modelPtr1->transform.SetVector3(Position, Vector3(10.0f, 0.0f, 0.0f));

		//modelPtr2 = std::static_pointer_cast<GZJModel>
		//	(modelMgrPtr->CreateRes("nanosuit"));
		//modelPtr2->SyncLoad();
		//modelPtr2->transform.SetVector3(Scale, Vector3(0.2, 0.2, 0.2));

		for (int i = 0; i < NUM_CUBE; ++i)
		{
			auto& cube = cubesModel[i];
			cube = std::static_pointer_cast<GZJModel>(
				modelMgrPtr->CreateRes("cube3"));
			cube->SyncLoad();
			cube->transform.SetVector3(Position,
				Vector3(rand() % 15, rand() % 15, rand() % 15));
			cube->transform.SetVector3(Rotation,
				Vector3(rand() % 360, rand() % 360, rand() % 360));
		}

		parallelLightModel = parallelLightPtr->GetModel();
		pointLightModel = pointLightPtr->GetModel();
		spotLightModel = spotLightPtr->GetModel();

		cout << showV3(spotLightModel->transform.GetVector3(Rotation)) << endl;
		cout << showV3(spotLightModel->transform.GetVector3(Front)) << endl;

		glEnable(GL_DEPTH_TEST);
		while (!glfwWindowShouldClose(win->GetWindow()) && game_is_running)
		{

			loops = 0;
			while (gzjTime->GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP)
			{
				update_game();
				next_game_tick += SKIP_TICKS;
				loops++;
			}
			display_game();



			win->Process();
		}
		//renderStaitc->ClearRenderDatas();
		win->Close();
		shaderMgrPtr->ShutDown();
		//eventSystemPtr->ShutDown();
		//meshMgrPtr->ShutDown();
		modelMgrPtr->ShutDown();
		resLoadPtr->ShutDown();
	}

	return 0;
}

void update_game() {
	gzjTime->Update();
	mainCamera.moveCmp->LogicUpdate();
}

void display_game() {
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//shader->Use();
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3); 
	//mesh->Draw(shader);
	Before_Draw();

	InitShader();

	/*modelPtr1->SetShader(shader1);
	modelPtr1->Draw();*/

	parallelLightModel->SetShader(shader1);
	parallelLightModel->Draw();
	pointLightModel->SetShader(shader1);
	pointLightModel->Draw();
	spotLightModel->SetShader(shader1);
	spotLightModel->Draw();

	//modelPtr2->SetShader(parallelLS);
	//parallelLS->Use();
	//modelPtr2->SetLight(LightType::Light_ParallelLight, parallelLightPtr);
	//modelPtr2->Draw();

	for (int i = 0; i < NUM_CUBE; ++i)
	{
		GZJModelPtr& cube = cubesModel[i];
		// parallel
		//cube->SetShader(parallelLS);
		//parallelLS->Use();
		//cube->SetLight(LightType::Light_ParallelLight, parallelLightPtr);
		// point
		//cube->SetShader(pointLS);
		//pointLS->Use();
		//cube->SetLight(LightType::Light_PointLight, pointLightPtr);
		// spot light
		cube->SetShader(spotLS);
		spotLS->Use();
		cube->SetLight(LightType::Light_SpotLight, spotLightPtr);

		cube->Draw();
	}

	//renderStaitc->Render();
}

void Before_Draw()
{
	/*mainCamera.SetVector3(CameraParam::Position, Vector3(0, 0, 10));
	mainCamera.SetVector3(CameraParam::Rotation, Vector3(0, 180, 0)); */
}

void InitShader()
{
	Vector4x4 projection;
	float tmp = 1.0f * win->GetInt(Win_Width) / win->GetInt(Win_Height);
	projection = glm::perspective(glm::radians(45.0f), tmp, 0.1f, 100.0f);

	// light
	shader1->Use();
	shader1->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
	shader1->SetMatrix(Shader_ViewToProjection, projection);

	// parallel light
	parallelLS->Use();
	parallelLS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
	parallelLS->SetMatrix(Shader_ViewToProjection, projection);
	parallelLS->SetVector3(View_ViewPosition, mainCamera.transform.GetVector3(Position));

	// point light
	pointLS->Use();
	pointLS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
	pointLS->SetMatrix(Shader_ViewToProjection, projection);
	pointLS->SetVector3(View_ViewPosition, mainCamera.transform.GetVector3(Position));

	// spot light
	spotLS->Use();
	spotLS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
	spotLS->SetMatrix(Shader_ViewToProjection, projection);
	spotLS->SetVector3(View_ViewPosition, mainCamera.transform.GetVector3(Position));

	// normal
	normalS->Use();
	normalS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
	normalS->SetMatrix(Shader_ViewToProjection, projection);

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Param_Press_KeyBoard param = Param_Press_KeyBoard(
		GZJWindow::GetInstance(), key, action);

	GZJEventSystem::GetInstance()->Fire(EV_Press_KeyBoard, static_cast<const GZJEventParamObj&>(param));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Param_Press_Mouse param = Param_Press_Mouse(
		GZJWindow::GetInstance(), button, action);

	GZJEventSystem::GetInstance()->Fire(EV_Press_Mouse, static_cast<const GZJEventParamObj&>(param));
}


