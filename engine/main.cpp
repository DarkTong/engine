#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GZJCommon.h"
#include "GZJRequire.h"
#include "GZJHeadFile.h"

#include "GZJTest.cpp"


using namespace GZJ_ENGINE;

GZJWindowPtr win = GZJWindow::GetInstance();
GZJTimePtr gzjTime = GZJTime::GetInstance();
GZJResourceLoadPtr resLoadPtr = GZJResourceLoad::GetInstance();
GZJShaderManagerPtr shaderMgrPtr = GZJShaderManager::GetInstance();
GZJModelManagerPtr modelMgrPtr = GZJModelManager::GetInstance();

//GZJCamera mainCamera;
GZJEventSystemPtr eventSystemPtr = GZJEventSystem::GetInstance();
//GZJModelManagerPtr modelMgrPtr = MakeShared<GZJModelManager>(new GZJModelManager());
//GZJRenderStaticPtr renderStaitc = GZJRenderStatic::GetInstance();

DWORD next_game_tick = GetTickCount();// 返回当前的系统已经运行的毫秒数
int loops;
bool game_is_running = true;
bool is_test_normal_func = false;

//// 用于临时操作
//void Before_Draw();
//// 设置shader的一些属性
//void InitShader();
//// 渲染场景
//void RenderScene(std::vector<GZJEntityPtr>& models, 
//	GZJShaderPtr shader, GZJLightPtr light=nullptr);

void update_game();
void display_game();
// 键盘按键回调
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// 鼠标按键
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


//GZJEntityPtr modelPtr1, nanosuit;
//GZJEntityPtr floorModel;
//const int NUM_CUBE = 5;
//std::vector<GZJEntityPtr> cubesModel;
//
//GZJShaderPtr shader1, shader2;
//GZJShaderPtr parallelLS, pointLS, spotLS, normalS,
//	pointLSS;
//GZJLightPtr parallelLightPtr, pointLightPtr, spotLightPtr;
//std::vector<GZJLightPtr> lightV;
//
//// depth id
//unsigned int depthBuffer = 0;
//unsigned int depthTexture = 0;
//GZJShaderPtr depthS, showTextureS;
//// build depth map
//void BuildDepthMap();
//// rendering to depth map
//void RenderToDepthMap(const GZJLightPtr& light);
//
//// rendering normal
//void RenderToNormal();

GZJScenePtr scenePtr;


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
		shaderMgrPtr->StartUp();
		//meshMgrPtr = std::dynamic_pointer_cast<GZJMeshManager>((new GZJMeshManager)->GetSelf());
		//meshMgrPtr->StartUp();
		modelMgrPtr->StartUp();


		// 临时 ---------------- create shader program ----------
		// build and compile our shader program
		// ------------------------------------
		//mainCamera.SetVector3(CameraParam::Position, Vector3(0, 0, -10));
		//mainCamera.moveCmp->moveSpeed = .007f;
		//mainCamera.moveCmp->pitchSpeed = .02f;
		//mainCamera.moveCmp->yawSpeed = .02f;
		//mainCamera.transform.SetVector3(Rotation, Vector3(0, 0, 180));
		//shader1 = std::static_pointer_cast<GZJShader>
		//	(shaderMgrPtr->FindResByName("whiteLight_1"));
		//parallelLS = std::static_pointer_cast<GZJShader>
		//	(shaderMgrPtr->FindResByName("parallel_light"));
		//pointLS = std::static_pointer_cast<GZJShader>
		//	(shaderMgrPtr->FindResByName("point_light"));
		//spotLS = std::static_pointer_cast<GZJShader>
		//	(shaderMgrPtr->FindResByName("spot_light"));
		//normalS = std::static_pointer_cast<GZJShader>
		//	(shaderMgrPtr->FindResByName("normal"));
		//depthS = std::static_pointer_cast<GZJShader>
		//	(shaderMgrPtr->FindResByName("depth_texture"));
		//showTextureS = std::static_pointer_cast<GZJShader>
		//	(shaderMgrPtr->FindResByName("show_texture"));
		//pointLSS = std::static_pointer_cast<GZJShader>
		//	(shaderMgrPtr->FindResByName("point_light_shadow"));

		//shader1->Prepare();
		//shader1->SyncLoad();
		//parallelLS->Prepare();
		//parallelLS->SyncLoad();
		//pointLS->Prepare();
		//pointLS->SyncLoad();
		//spotLS->Prepare();
		//spotLS->SyncLoad();
		//normalS->Prepare();
		//normalS->SyncLoad();
		//depthS->Prepare();
		//depthS->SyncLoad();
		//showTextureS->Prepare();
		//showTextureS->SyncLoad();
		//pointLSS->Prepare();
		//pointLSS->SyncLoad();

		//floorModel = MakeShared<GZJEntity>();
		//floorModel->model = std::static_pointer_cast<GZJModel>
		//	(modelMgrPtr->FindResByName("floor"));
		//floorModel->model->SyncLoad();
		//floorModel->transform.SetVector3(Position, Vector3(5, 0, 5));

		//nanosuit = MakeShared<GZJEntity>();
		//nanosuit->model = std::static_pointer_cast<GZJModel>
		//	(modelMgrPtr->FindResByName("nanosuit"));
		//nanosuit->model->SyncLoad();
		//nanosuit->transform.SetVector3(Scale, Vector3(0.3, 0.3, 0.3 ));
		//nanosuit->transform.SetVector3(Position, Vector3(1, 1, 4));
		//nanosuit->transform.SetVector3(Rotation, Vector3(0, 180, 0));

		//cubesModel.push_back(nanosuit);
		//cubesModel.push_back(floorModel);

		//for (int i = 0; i < NUM_CUBE; ++i)
		//{
		//	GZJEntityPtr cube;
		//	cube = MakeShared<GZJEntity>();
		//	cube->model = std::static_pointer_cast<GZJModel>(
		//		modelMgrPtr->FindResByName("cube3"));
		//	cube->model->SyncLoad();
		//	cube->transform.SetVector3(Position,
		//		Vector3(rand() % 5, rand() % 5, rand() % 5));
		//	cube->transform.SetVector3(Rotation,
		//		Vector3(rand() % 360, rand() % 360, rand() % 360));

		//	cubesModel.push_back(cube);
		//}
		//cubesModel.push_back(floorModel);
		scenePtr = MakeShared<GZJScene>(3);
		scenePtr->ParseConfig();
		scenePtr->Load();

		// apply depth buffer
		//BuildDepthMap();
		//glEnable(GL_CULL_FACE);
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
// render floor
//GLuint quadVAO = 0;
//GLuint quadVBO;
//void RenderQuad()
//{
//	if (quadVAO == 0)
//	{
//		GLfloat quadVertices[] = {
//			// Positions        // Texture Coords
//			-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
//			-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
//			1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
//			1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
//		};
//		// Setup plane VAO
//		glGenVertexArrays(1, &quadVAO);
//		glGenBuffers(1, &quadVBO);
//		glBindVertexArray(quadVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	}
//	glBindVertexArray(quadVAO);
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glBindVertexArray(0);
//}

void update_game() {
	gzjTime->Update();
	//mainCamera.moveCmp->LogicUpdate();
	eventSystemPtr->Fire(EV_Login_Update, Param_Logic_Update());
}

//void BuildDepthMap()
//{	
//	Vector2 winSize = win->GetSize();
//	glGenTextures(1, &depthTexture);
//	glBindTexture(GL_TEXTURE_2D, depthTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
//		winSize.x, winSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
//	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//
//	// 将它附加到当前绑定的帧缓冲对象
//	glGenFramebuffers(1, &depthBuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
//		GL_TEXTURE_2D, depthTexture, 0);
//	glDrawBuffer(GL_NONE);
//	glReadBuffer(GL_NONE);
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void RenderToDepthMap(const GZJLightPtr& light)
//{
//	auto PrepareDepthShader = [light] {
//		depthS->Use();
//		depthS->SetMatrix(Shader_Light_Space, light->GetMatrix(LightData_LightSpace));
//		depthS->SetVector3(Light_Position,
//			light->GetEntity()->transform.GetVector3(Position));
//		depthS->SetFloat(Light_Near_Plane,
//			light->GetFloat(LightData_Near_Plane));
//		depthS->SetFloat(Light_Far_Plane,
//			light->GetFloat(LightData_Far_Plane));
//	};
//
//	// 切换到深度帧缓存，之后的所有渲染操作将写到深度帧缓存中
//	glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
//	// 清空帧缓存中的深度数据
//	glClear(GL_DEPTH_BUFFER_BIT);
//	// 开启深度测试，只有开启深度设置才会有深度值，才会写入深度贴图
//	glEnable(GL_DEPTH_TEST);
//	// 准备渲染深度贴图的shader的数据
//	PrepareDepthShader();
//	// 渲染场景
//	RenderScene(cubesModel, depthS);
//	// 切换到默认帧缓存，只有默认帧缓存才会渲染到屏幕上
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	// 激活0号纹理
//	glActiveTexture(GL_TEXTURE0);
//	// 将深度贴图绑定到0号纹理上
//	glBindTexture(GL_TEXTURE_2D, depthTexture);
//
//	// test
//	glDisable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	showTextureS->Use();
//	RenderQuad();
//
//}
//
//void RenderToNormal()
//{
//	// 开启深度贴图
//	glEnable(GL_DEPTH_TEST);
//	// 清空颜色缓存和深度缓存
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	std::vector<GZJEntityPtr> lightModel = {pointLightPtr->GetEntity()};
//	// 渲染光源
//	RenderScene(lightModel, shader1);
//	// 渲染场景
//	RenderScene(cubesModel, pointLSS, pointLightPtr);
//}

void display_game() {
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	////glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	////InitShader();
	//glCullFace(GL_FRONT);
	//RenderToDepthMap(pointLightPtr);
	//glCullFace(GL_BACK); // 不要忘记设回原先的culling face

	//RenderToNormal();

	//renderStaitc->Render();

	scenePtr->Render();
}

//void RenderScene(std::vector<GZJEntityPtr>& models, GZJShaderPtr shader, GZJLightPtr light)
//{
//	if(light != nullptr)
//		light->SetToShader(shader);
//	for (int i = 0; i < models.size(); ++i)
//	{
//		GZJEntityPtr entity = models[i];
//		entity->Draw();
//	}
//}
//
//void Before_Draw()
//{
//	/*mainCamera.SetVector3(CameraParam::Position, Vector3(0, 0, 10));
//	mainCamera.SetVector3(CameraParam::Rotation, Vector3(0, 180, 0)); */
//}
//
//void InitShader()
//{
//	//Vector4x4 projection;
//	//float tmp = 1.0f * win->GetInt(Win_Width) / win->GetInt(Win_Height);
//	//projection = glm::perspective(glm::radians(45.0f), tmp, 0.1f, 100.0f);
//
//	//// light
//	//shader1->Use();
//	//shader1->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
//	//shader1->SetMatrix(Shader_ViewToProjection, projection);
//
//	//// parallel light
//	//parallelLS->Use();
//	//parallelLS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
//	//parallelLS->SetMatrix(Shader_ViewToProjection, projection);
//	//parallelLS->SetVector3(View_ViewPosition, mainCamera.transform.GetVector3(Position));
//
//	//// point light
//	//pointLS->Use();
//	//pointLS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
//	//pointLS->SetMatrix(Shader_ViewToProjection, projection);
//	//pointLS->SetVector3(View_ViewPosition, mainCamera.transform.GetVector3(Position));
//
//	//// spot light
//	//spotLS->Use();
//	//spotLS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
//	//spotLS->SetMatrix(Shader_ViewToProjection, projection);
//	//spotLS->SetVector3(View_ViewPosition, mainCamera.transform.GetVector3(Position));
//
//	//// normal
//	//normalS->Use();
//	//normalS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
//	//normalS->SetMatrix(Shader_ViewToProjection, projection);
//
//	//// point light shadow
//	//pointLSS->Use();
//	//pointLSS->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
//	//pointLSS->SetMatrix(Shader_ViewToProjection, projection);
//	//pointLSS->SetVector3(View_ViewPosition, mainCamera.transform.GetVector3(Position));
//
//}

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


