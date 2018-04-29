#ifndef __GZJ_EVENT_PARAM_OBJ_
#define __GZJ_EVENT_PARAM_OBJ_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GZJRequire.h"
#include "GZJWindow.h"

namespace GZJ_ENGINE {
	/** 事件参数基类
	*/
	class GZJEventParamObj {};

	class Param_Press_KeyBoard :public GZJEventParamObj
	{
	public:
		GZJWindowPtr window;
		int key;
		int action;
		Param_Press_KeyBoard(GZJWindowPtr win, int key, int action)
			:window(win), key(key), action(action) {}
	};

	class Param_Press_Mouse :public GZJEventParamObj
	{
	public:
		GZJWindowPtr window;
		int key;
		int action;
		Param_Press_Mouse(GZJWindowPtr win, int key, int action)
			:window(win), key(key), action(action) {}
	};

	class Param_Logic_Update :public GZJEventParamObj
	{
		
	};
}

#endif // !__GZJ_EVENT_PARAM_OBJ_


