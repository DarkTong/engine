#ifndef _GZJ_RESOURCE_
#define _GZJ_RESOURCE_

#include "GZJRequire.h"
#include "GZJResourceManager.h"

namespace GZJ_ENGINE {

	class GZJResource {
	public:
		/** 资源类
		@param 管理当前资源的管理者
		@param 资源的相对路径
		*/
		GZJResource(GZJResourceManagerPtr manager, const String& name, ResourceHandle handle);
	protected:

		GZJResourceManagerPtr _mgr;
		String _path;
		ResourceHandle _handle;
		String _name;
		ResState _state;

	public:
		///** 准备资源来准备加载
		//*/
		//virtual void Prepare( ... ) = 0;

		/** 加载资源
		*/
		virtual void Load() = 0;

		/** 卸载资源
		*/
		virtual void Unload() = 0;
		
	};
}
#endif // !_GZJ_RESOURCE_
