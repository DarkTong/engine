#include "GZJRequire.h"

namespace GZJ_ENGINE {
	/** 资源句柄
	*/
	typedef unsigned long long ResourceHandle;

	/** 资源状态
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
		/** 资源类
		@param 管理当前资源的管理者
		@param 资源的相对路径
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
		/** 准备资源来准备加载
		*/
		virtual void prepare() = 0;
		/** 加载资源
		*/
		virtual void load() = 0;
		/** 卸载资源
		*/
		virtual void unload() = 0;
		
	};
}
