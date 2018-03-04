#include "GZJRenderStatic.h"

namespace GZJ_ENGINE {
	GZJRenderStaticPtr GZJRenderStatic::_instance = nullptr;

	void GZJRenderStatic::PrepareRender() {

		for (int idx = 0; idx < renderDatas.size(); ++idx) {
			RenderUtil& data = renderDatas[idx];

			if (!data.hadPrepared) {
				Do_PrepareRender(data);
			}
		}
	}

	void GZJRenderStatic::Do_PrepareRender(RenderUtil & data)
	{
		glGenVertexArrays(1, &data.VAO);
		glGenBuffers(1, &data.VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(data.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, data.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data.vertices), data.vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		data.hadPrepared = true;
	}

	void GZJRenderStatic::Render() {
		for (int idx = 0; idx < renderDatas.size(); ++idx) {
			RenderUtil& data = renderDatas[idx];
			if (!data.hadPrepared)
				Do_PrepareRender(data);
			glUseProgram(data.shaderProgram);
			glBindVertexArray(data.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	void GZJRenderStatic::AddRenderData(const RenderUtil& data) {
		RenderUtil _data = data;
		_data.hadPrepared = false;
		renderDatas.push_back(_data);
	}

	void GZJRenderStatic::ClearRenderDatas() {
		for (int idx = 0; idx < renderDatas.size(); ++idx) {
			RenderUtil& data = renderDatas[idx];

			glDeleteVertexArrays(1, &data.VAO);
			glDeleteBuffers(1, &data.VBO);

			data.hadPrepared = false;
		}
	}
}
