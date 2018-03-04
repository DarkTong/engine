#include "GZJRequire.h"

namespace GZJ_ENGINE {
	struct RenderUtil {
		int shaderProgram;
		float *vertices;
		unsigned int VAO, VBO;
		bool hadPrepared;
		RenderUtil(int shaderProgram, float *vertices) :
			shaderProgram(shaderProgram), vertices(vertices) {
			VAO = VBO = 0;
			hadPrepared = false;
		}
	};

	class GZJRender {
	public:
		virtual void Render() = 0;
	};
}
