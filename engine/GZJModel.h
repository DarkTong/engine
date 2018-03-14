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
    };
}

#endif //__GZJ_MODEL__
