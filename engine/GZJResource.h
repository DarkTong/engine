#ifndef _GZJ_RESOURCE_
#define _GZJ_RESOURCE_

#include "GZJRequire.h"
#include "GZJResourceManager.h"

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

	public:
		/** ׼����Դ��׼������
		*/
		void Prepare();

		/** ������Դ
		*/
		virtual void Load() = 0;

		/** ж����Դ
		*/
		virtual void Unload() = 0;

		/** ������Դ״̬
		*/
		void SetState(ResState state);
		
		/** ��ȡ��Դ״̬
		*/
		ResState GetState() const;
	};
}
#endif // !_GZJ_RESOURCE_
