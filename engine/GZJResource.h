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
		GZJResource(GZJResourceManager* manager, const String& name, ResourceHandle handle);
	protected:

		GZJResourceManager* _mgr;
		String _path;
		ResourceHandle _handle;
		String _name;
		ResState _state;

	public:
		/** 准备资源来准备加载
		*/
		void Prepare();

		/** 加载资源
		*/
		virtual void Load() = 0;

		/** 卸载资源
		*/
		virtual void Unload() = 0;

		/** 设置资源状态
		*/
		void SetState(ResState state);
		
		/** 获取资源状态
		*/
		ResState GetState() const;
	};
}
#endif // !_GZJ_RESOURCE_
