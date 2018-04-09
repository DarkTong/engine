#ifndef __GZJ_TEXTURE_MANAGER_
#define __GZJ_TEXTURE_MANAGER_

#include "GZJRequire.h"
#include "GZJResourceManager.h"
#include "GZJTexture.h"

namespace GZJ_ENGINE {
	class GZJTextureManager :public GZJResourceManager
	{
		/* ����
		*/
	private:
		static GZJTextureManagerPtr _instance;
	public:
		static GZJTextureManagerPtr GetInstance()
		{
			if (_instance == nullptr)
				_instance = MakeShared<GZJTextureManager>();
			return _instance;
		}

	public:
		// ���졢����
		GZJTextureManager();

		~GZJTextureManager();

	public:
		// �̳�
		void StartUp();

		void ShutDown();

	private:
		// ��ʹ��

		/** ׼��������Դ
		*/
		void PrepareAll();

		/** ����������Դ
		*/
		void LoadAll();

		/** ж��������Դ
		*/
		void UnLoadAll();

	private:
		// �̳�

		GZJResource* createImp(const String &name);
	};
}

#endif // !__GZJ_TEXTURE_MANAGER_
