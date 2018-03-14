#include "GZJMesh.h"

namespace GZJ_ENGINE {
	GZJMesh::GZJMesh(GZJResourceManagerPtr manager, const String & name
		, ResourceHandle handle)
		:GZJResource(manager, name, handle)
	{
		
		// 临时处理
		_path = manager->GetResRoot() + "\\" + name;
		_state = ResState::UNPREPARE;
	}
	void GZJMesh::Prepare(Vertices ver, Indices ind, Textures tex)
	{
		vertices = ver;
		indices = ind;
		textures = tex;
		std::cout << vertices.size() << " "
			<< indices.size() << " " 
			<< textures.size() << std::endl;
		_state = ResState::UNLOAD;
	}
	void GZJMesh::Load()
	{
		if (_state == ResState::UNLOAD) {
			std::cout << "OK!!!" << std::endl;
			std::cout << vertices.size() << std::endl;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

			// 定点位置
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

			// 法线
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

			// 贴图位置
			 glEnableVertexAttribArray(2);
			 glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

			glBindVertexArray(0);

			_state = ResState::LOADED;
		}
	}
	void GZJMesh::Unload()
	{
		if (_state = ResState::LOADED) {
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &EBO);
			glDeleteBuffers(1, &VBO);

			_state = ResState::UNLOAD;
		}
	}
	void GZJMesh::Draw(GZJShaderPtr shader)
	{
		if (_state = ResState::LOADED) {

			// todo 加载贴图


			// 渲染
			//std::cout << "state:" << shader->GetState() << " " << VAO <<  std::endl;
			shader->Use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		else{
			std::cout << "Mesh Resource is not Loaded!!!" << std::endl;
			assert(false);
		}
	}
}
