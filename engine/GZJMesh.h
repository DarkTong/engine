#pragma once

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJShader.h"

namespace GZJ_ENGINE {

	struct Vertex {
		/** ����
		*/
		Vector3 position;
		/** ������
		*/
		Vector3 normal;
		/** ��ͼ
		*/
		Vector2 texCoords;

	};

	typedef std::vector<Vertex> Vertices;
	typedef std::vector<unsigned int> Indices;
	typedef std::vector<GZJTexturePtr> Textures;


	class GZJMesh{
	private:
		// ��̬ȫ������
		static const int MAX_MATERIAL = 1;
	private:
		// GPU���
		unsigned int VAO, VBO, EBO;
	public:
		/** ���еĶ�����Ϣ
		*/
		Vertices vertices;
		/** ���е�������Ϣ
		*/
		Indices indices;
		/** ���е���ͼ
		*/
		Textures textures;

		/** ���������ɫ
		*/
		Vector3 diffuseColor;
		Vector3 specularColor;
	public:
		
		GZJMesh();
		
		~GZJMesh();
		
		/** ��Ⱦ
		@param ��Ⱦ����
		*/
		void Draw(GZJShaderPtr shader);

		/** �Ƿ��Ѿ���GPU�������ڴ���
		*/
		bool IsLoginGPU();

		/** ���ض������ݵ��ڴ�
		*/
		void LoginGPU();

		/** ж�ض�������
		*/
		void LogoutGPU();
	};
}

#include "GZJResourceManager.h"
#include "GZJTextureManager.h"
