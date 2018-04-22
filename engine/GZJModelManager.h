#ifndef __GZJ_MODEL_MANAGER__
#define __GZJ_MODEL_MANAGER__

#include "GZJRequire.h"
#include "GZJModel.h"
#include "GZJMeshManager.h"

namespace GZJ_ENGINE {
	class GZJModelManager :public GZJResourceManager {
	public:
		// ������
		static GZJModelManagerPtr _instance;
		static GZJModelManagerPtr GetInstance();

	public:
		GZJModelManager();
		
		~GZJModelManager();

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

	protected:
		// ���ڽӿ�
		GZJResource* createImp(const String& name);

	};
}

#endif // !__GZJ_MODEL_MANAGER__
