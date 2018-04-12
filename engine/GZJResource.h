#ifndef _GZJ_RESOURCE_
#define _GZJ_RESOURCE_

#include <mutex>

#include "GZJRequire.h"
#include "GZJResourceManager.h"
#include "GZJResourceLoad.h"

namespace GZJ_ENGINE {

	class GZJResource {
	public:
		/** ��Դ��
		@param ����ǰ��Դ�Ĺ�����
		@param ��Դ�����·��
		*/
		GZJResource(GZJResourceManager* manager, const String& name, ResourceHandle handle);
	protected:

		GZJResourceManager* _mgr;
		String _path;
		ResourceHandle _handle;
		String _name;
		ResState _state;

	private:
		/** ������Դ״̬����
		*/
		mutable std::mutex mutexToState;

	public:
		/** ׼����Դ��׼������
		*/
		void Prepare();

		/** ͬ��������Դ
		*/
		void SyncLoad();

		/** �첽������Դ
		*/
		void AsyncLoad();

		/** ж����Դ
		*/
		void UnLoad();

		/** ������Դ״̬
		*/
		void SetState(ResState state);
		
		/** ��ȡ��Դ״̬
		*/
		ResState GetState() const;

		/** ��ȡ��Դ����
		*/
		virtual ResourceType GetResType() = 0;

	private:
		// ���ڽӿ�

		/** ������Դ
		*/
		void Load();

		/** ʵ�м�����Դ
		*/
		virtual void DoLoad() = 0;

		/** ʵ��ж����Դ
		*/
		virtual void DoUnLoad() = 0;

	};
}
#endif // !_GZJ_RESOURCE_
