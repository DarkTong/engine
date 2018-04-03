#ifndef __GZJ_EVENT_PARAM_OBJ_
#define __GZJ_EVENT_PARAM_OBJ_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GZJRequire.h"

namespace GZJ_ENGINE {
	/** 事件参数基类
	*/
	class GZJEventParamObj {};

	class EV_Press_KeyBoard :public GZJEventParamObj
	{
		GZJWindowPtr win;
		int key;
	};

	class EV_Press_Mouse :public GZJEventParamObj
	{
		GZJWindowPtr win;
		int key;
	};
}

#endif // !__GZJ_EVENT_PARAM_OBJ_


