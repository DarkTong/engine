#ifndef __GZJ_WINDOW_
#define __GZJ_WINDOW_

#include "GZJRequire.h"

#include "string"

namespace GZJ_ENGINE {
	enum WindowData {
		Win_Width,
		Win_Height,
	};

	class GZJWindow {
	private:
		static GZJWindowPtr _instance;
	public:
		// ����
		static GZJWindowPtr GetInstance() {
			if (_instance == nullptr) {
				_instance = std::make_shared<GZJWindow>(1600, 900);
			}
			return _instance;
		}

	private:
		std::string WIN_NAME;
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;
		GLFWwindow* window;

	private:
		

	public:
		GZJWindow(unsigned int scr_width = 1600, unsigned int scr_height = 900) :
			SCR_WIDTH(scr_width), SCR_HEIGHT(scr_height) {
			window = nullptr;
			WIN_NAME = "GZJ_ENGINE";
		}

		friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		void SetWinName(std::string win_name);

		void InitWindow();

		void BuildWindow();

		GLFWwindow* GetWindow();

		void Process();

		void Close();

	public:
		/** ��ȡ��Ӧ����
		*/
		int GetInt(WindowData param);

		/** ��ȡ��ǰ���ڵ����λ��
		*/
		Vector2 GetCursorPos();
	};
}

#endif // !__GZJ_WINDOW_
