#include "GZJRequire.h"

namespace GZJ_ENGINE {
	/** ��Դ���
	*/
	typedef unsigned long long ResourceHandle;

	/** ��Դ״̬
	*/
	enum ResState {
		UNPREPARE,
		PREPAREING,
		UNLOAD,
		LOADING,
		LOADED,
		OLDED,
	};

	class GZJResource {
	public:
		/** ��Դ��
		@param ����ǰ��Դ�Ĺ�����
		@param ��Դ�����·��
		*/
		GZJResource(GZJResourceManagerPtr manager, const String& path
			, const String& name, ResourceHandle handle);
	protected:

		GZJResourceManagerPtr _mgr;
		String _path;
		ResourceHandle _handle;
		String _name;
		ResState _state;

	public:
		/** ׼����Դ��׼������
		*/
		virtual void prepare() = 0;
		/** ������Դ
		*/
		virtual void load() = 0;
		/** ж����Դ
		*/
		virtual void unload() = 0;
		
	};
}
