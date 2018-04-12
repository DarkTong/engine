#ifndef __GZJ_RESOURCE_LOAD_
#define __GZJ_RESOURCE_LOAD_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

#include "GZJRequire.h"

#include "GZJResource.h"

namespace GZJ_ENGINE{

	enum ResLoadState
	{
		ResLoadState_Open,
		ResLoadState_Close,
		ResLoadState_Free,
		ResLoadState_Busy,
	};

	class GZJResourceLoad
	{
		/** ����
		*/
	public:
		static GZJResourceLoadPtr _instance;

		static GZJResourceLoadPtr GetInstance();
		
		GZJResourceLoad();

		~GZJResourceLoad();

	private:
		/** ��������Դ������
		*/
		const static int NUMBER_OF_RES_TYPE = 3;

		/** �����ص���Դ����
		*/
		std::queue<GZJResourcePtr> _resQueue[NUMBER_OF_RES_TYPE];
		
		/** ��¼�߳�����
		*/
		std::thread _threadGroup[NUMBER_OF_RES_TYPE];

		/** ��¼��ǰ�߳�״̬
		*/
		ResLoadState _threadState[NUMBER_OF_RES_TYPE];

		/** ��Ӧ�Ķ��е���
		*/
		std::mutex _threadMutex[NUMBER_OF_RES_TYPE];

		/**��Ӧ�̵߳���������
		*/
		std::condition_variable _threadFlag[NUMBER_OF_RES_TYPE];

	public:
		// ����ӿ�

		void StartUp();

		void ShutDown();

		/** ��Ӵ�������Դ
		*/
		void AddRes(GZJResourcePtr resPtr, ResourceType type);

	public:
		// ��Ӧ����Դ������
		
		void DoLoadTextureRes();

		void DoLoadMeshRes();

		void DoLoadModelRes();

	};
}

#endif // !__GZJ_RESOURCE_LOAD_
