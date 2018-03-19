#ifndef __GZJ_MODEL__
#define __GZJ_MODEL__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJResourceManager.h"
#include "GZJMeshManager.h"
#include "GZJMesh.h"
#include "GZJShader.h"

namespace GZJ_ENGINE{
    class GZJModel : public GZJResource{
    public:
		/** ��Դ��
		@param ����ǰ��Դ�Ĺ�����
		@param ��Դ�����·��
		*/
		GZJModel(GZJResourceManagerPtr manager, const String& name, ResourceHandle handle);

	private:
		/** mesh��Դ����
		*/
		GZJMeshManager meshMgr;

		/** shader
		*/
		GZJShaderPtr shader;

		/** ��¼ĳ�������Ƿ��ȡ��
		*/
		std::map<ShaderData, bool> dataRec;

		/** ��������shader������
		*/
		std::map<unsigned int, float> dataVec1;
		std::map<unsigned int, Vector2> dataVec2;
		std::map<unsigned int, Vector3> dataVec3;
		std::map<unsigned int, Vector4x4> dataMat4;


	public:
		///** ׼����Դ��׼������
		//*/
		//virtual void Prepare( ... ) = 0;

		/** ������Դ
		*/
		void Load();

		/** ж����Դ
		*/
		void Unload();

		/** ��Ⱦ
		 * param : ��ɫ��
		*/
		void Draw();

		/** ����������Ⱦ��shader
		 * param : shader
		*/
		void SetShader(GZJShaderPtr shader);

		/** ����Shader�ĸ�������
		*/
		void SetShaderData();

	private:
		/** ����assimp�Ľڵ���Ϣ
		@param assimp�ڵ�
		@param assimp����
		*/
		void ProcessNode(aiNode *node, const aiScene *scene);

		/** ����assimp��������Ϣ
		@param assimp����
		@param assimp����
		*/
		void ProcessMesh(aiMesh *mesh, const aiScene *scene);

		/** prepare
		*/

	public:
		/* ���������Shader���ݽӿ�
		*/
		void SetVec1(ShaderData shaderData, Vector3 vec1);
		void SetVec2(ShaderData shaderData, Vector3 vec2);
		void SetVec3(ShaderData shaderData, Vector3 vec3);
		void SetMat4(ShaderData shaderData, Vector4x4 mat4);

	private:
		/** �������shaderData����
		*/
		void DoTransform(Vector4x4 mat4);
    };
}

#endif //__GZJ_MODEL__
