#include "GZJRequire.h"

#include "string"

namespace GZJ_ENGINE {

	class GZJWindow {

	private:
		std::string WIN_NAME;
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;
		GLFWwindow* window;

	private:
		

	public:
		GZJWindow(unsigned int scr_width = 800, unsigned int scr_height = 600) :
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
	};
}