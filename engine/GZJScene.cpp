#include "GZJScene.h"

namespace GZJ_ENGINE
{
	const String GZJScene::CONFIG_PATH_PRE
		= ENGINE_SRC_ROOT_PATH + "\\config\\scene";

	GZJScene::GZJScene(unsigned int id)
	{
		_id = id;
		isOpenShadow = false;
		configPath = CONFIG_PATH_PRE + "\\" 
			+ std::to_string(id) + "\\scene.xml";

		shaderMgr = GZJShaderManager::GetInstance();
		modelMgr = GZJModelManager::GetInstance();
		win = GZJWindow::GetInstance();
	}

	GZJScene::~GZJScene()
	{
	}

	void GZJScene::DoParseConfig(TiXmlElement * ele)
	{
		for (TiXmlElement* child = ele->FirstChildElement();
			child != nullptr;
			child = child->NextSiblingElement())
		{
			if (child->ValueTStr() == "entity")
				DoParseEntityData(child);
			else if (child->ValueTStr() == "light")
				DoParseLightData(child);
			else if (child->ValueTStr() == "main_camera")
				DoParseMainCameraData(child);
			else if (child->ValueTStr() == "shadow")
				DoParseShadowData(child);
		}
	}

	void GZJScene::DoParseLightData(TiXmlElement * ele)
	{
		String lightType = ele->FirstChildElement("type")->GetText();
		// �������ʹ���������Դ
		// Ȼ���ʼ����Դ
		GZJLightPtr lightPtr;
		if (lightType == "ParallelLight")
		{
			lightPtr = std::static_pointer_cast<GZJLight>(
				MakeShared<GZJParallelLight>());
		}
		else if (lightType == "PointLight")
		{
			lightPtr = std::static_pointer_cast<GZJLight>(
				MakeShared<GZJPointLight>());
		}
		else if (lightType == "SpotLight")
		{
			lightPtr = std::static_pointer_cast<GZJLight>(
				MakeShared<GZJSpotLight>());
		}
		else
		{
			cout << "not contain this light type!!, type:" << lightType << endl;
			return;
		}

		lightPtr->ParseLightData(ele);
		lightMap[lightPtr->GetID()] = lightPtr;
	}

	void GZJScene::DoParseEntityData(TiXmlElement * ele)
	{
		int create_number = 1;
		auto create_number_str = ele->Attribute("create_number");
		if (create_number_str)
			create_number = atoi(create_number_str);
		for (int i = 0; i < create_number; ++i)
		{
			GZJEntityPtr entity = MakeShared<GZJEntity>();
			entity->ParseData(ele);
			entityArr.push_back(entity);
		}
	}

	void GZJScene::DoParseMainCameraData(TiXmlElement * ele)
	{
		mainCamera.ParseData(ele);
	}

	void GZJScene::DoParseShadowData(TiXmlElement * ele)
	{
		const char * _shadow = ele->Attribute("flag");
		if (_shadow && String(_shadow) == "true")
			isOpenShadow = true;

		String shaderName = ele->FirstChildElement("shader")->GetText();
		depthShader = std::static_pointer_cast<GZJShader>(
			shaderMgr->FindResByName(shaderName));
	}

	void GZJScene::DoLoad()
	{
	}

	void GZJScene::DoUnLoad()
	{
	}

	void GZJScene::BuildDepthMap()
	{
		Vector2 winSize = win->GetSize();
		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			winSize.x, winSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		// �������ӵ���ǰ�󶨵�֡�������
		glGenFramebuffers(1, &depthBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D, depthTexture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GZJScene::ParseConfig()
	{
		TiXmlDocument doc;

		if (!doc.LoadFile(configPath.c_str()))
		{
			cout << "read light file fail!!, path:" << configPath << endl;
			return;
		}

		DoParseConfig(doc.RootElement());
	}

	void GZJScene::Load()
	{
		// ����entityArr
		GZJShaderPtr shaderPtr;
		for (int i = 0; i < entityArr.size(); ++i)
		{
			entityArr[i]->model->Prepare();
			entityArr[i]->model->SyncLoad();

			shaderPtr = entityArr[i]->shader;
			shaderPtr->Prepare();
			shaderPtr->SyncLoad();

			shaderMap[shaderPtr->GetShaderID()] = shaderPtr;
		}
		
		// ���ع���
		for (auto it=lightMap.begin(); it != lightMap.end(); ++it)
		{
			it->second->GetEntity()->model->Prepare();
			it->second->GetEntity()->model->SyncLoad();

			shaderPtr = it->second->GetEntity()->shader;
			shaderPtr->Prepare();
			shaderPtr->SyncLoad();

			shaderMap[shaderPtr->GetShaderID()] = shaderPtr;
		}

		// �������֡����
		if (isOpenShadow)
		{
			BuildDepthMap();
			depthShader->Prepare();
			depthShader->SyncLoad();

			shaderMap[depthShader->GetShaderID()] = depthShader;
		}
	}

	void GZJScene::UnLoad()
	{
		// ����entityArr
		for (int i = 0; i < entityArr.size(); ++i)
		{
			entityArr[i]->model->UnLoad();
		}
		// ���ع���
		for (auto it = lightMap.begin(); it != lightMap.end(); ++it)
		{
			it->second->GetEntity()->model->UnLoad();
		}
	}

	void GZJScene::RenderToDepth()
	{
		auto PrepareDepthShader = [this](GZJLightPtr light) {
			depthShader->Use();
			depthShader->SetMatrix(Shader_Light_Space, light->GetMatrix(LightData_LightSpace));
			depthShader->SetVector3(Light_Position,
				light->GetEntity()->transform.GetVector3(Position));
			depthShader->SetFloat(Light_Near_Plane,
				light->GetFloat(LightData_Near_Plane));
			depthShader->SetFloat(Light_Far_Plane,
				light->GetFloat(LightData_Far_Plane));
		};

		// �л������֡���棬֮���������Ⱦ������д�����֡������
		glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
		// ���֡�����е��������
		glClear(GL_DEPTH_BUFFER_BIT);
		// ������Ȳ��ԣ�ֻ�п���������òŻ������ֵ���Ż�д�������ͼ
		glEnable(GL_DEPTH_TEST);
		// �������޳�
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		for (auto it = lightMap.begin(); it != lightMap.end(); ++it)
		{
			// ׼����Ⱦ�����ͼ��shader������
			PrepareDepthShader(it->second);
			// ��Ⱦ����
			for (int i = 0; i < entityArr.size(); ++i)
			{
				entityArr[i]->Draw(depthShader);
			}
		}
		// ��Ҫ�������ԭ�ȵ�culling face
		glCullFace(GL_BACK); 
		// �л���Ĭ��֡���棬ֻ��Ĭ��֡����Ż���Ⱦ����Ļ��
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// ����0������
		glActiveTexture(GL_TEXTURE0);
		// �������ͼ�󶨵�0��������
		glBindTexture(GL_TEXTURE_2D, depthTexture);

		// test
		//glDisable(GL_DEPTH_TEST);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//showTextureS->Use();
		//RenderQuad();
	}

	void GZJScene::RenderToNormal()
	{
		// ���������ͼ
		glEnable(GL_DEPTH_TEST);
		// �����ɫ�������Ȼ���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// ����shader
		for (auto light = lightMap.begin(); light != lightMap.end(); ++light)
		{
			for (auto shader = shaderMap.begin(); shader != shaderMap.end(); ++shader)
			{
				light->second->SetToShader(shader->second);
				shader->second->Use();
				shader->second->SetMatrix(Shader_WorldToView, mainCamera.LookAt());
				shader->second->SetMatrix(Shader_ViewToProjection, mainCamera.Projection());
				shader->second->SetInt(Shader_IsOpenShadow, isOpenShadow);
				shader->second->SetVector3(View_ViewPosition, mainCamera.transform.GetVector3(Position));
			}

			// ��Ⱦ����
			for (int i = 0; i < entityArr.size(); ++i)
			{
				entityArr[i]->Draw();
			}

			// ��Ⱦ��Դ
			light->second->GetEntity()->Draw();
		}
	}

	void GZJScene::Render()
	{
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		if (isOpenShadow)
			RenderToDepth();
		//glEnable(GL_CULL_FACE);
		RenderToNormal();
	
	}

}
