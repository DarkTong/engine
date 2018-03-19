#ifndef _GZJ_MESH_MANAGER_
#define _GZJ_MESH_MANAGER_

#include "GZJRequire.h"
#include "GZJResourceManager.h"
#include "GZJMesh.h"
#include "GZJShader.h"

namespace GZJ_ENGINE {
	class GZJMeshManager :public GZJResourceManager 
	{
	private:
		GZJResource * createImp(const String& name);
	public:
		GZJMeshManager();

		~GZJMeshManager();

	public:
		/** ����������
		*/
		void StartUp();

		/** �رչ�����
		*/
		void ShutDown();

		/** ׼��������Դ
		*/
		void PrepareAll();
	public:
		/* �����Խӿڣ����е�
		*/

		/** ��Ⱦȫ��mesh
		*/
		void DrawAll(GZJShaderPtr shader = nullptr);
	};
}

#endif // !_GZJ_MESH_MANAGER_
