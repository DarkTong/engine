#include "GZJMesh.h"

namespace GZJ_ENGINE {
	GZJMesh::GZJMesh()
	{
		VAO = VBO = EBO = GL_NONE;
	}

	GZJMesh::~GZJMesh()
	{
		if(IsLoginGPU())
			LogoutGPU();
		// 释放贴图资源
		for (int idx = 0; idx < textures.size(); ++idx)
			textures[idx]->UnLoad();
	}

	void GZJMesh::LoginGPU()
	{
		if (IsLoginGPU())
			LogoutGPU();
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

		// 法线空间位置
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof Vertex, (void*)offsetof(Vertex, tangentVertex));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof Vertex, (void*)offsetof(Vertex, bitangentVertex));

		glBindVertexArray(0);
	}
	
	void GZJMesh::LogoutGPU()
	{
		if (IsLoginGPU())
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &EBO);
			glDeleteBuffers(1, &VBO);
		}
	}

	bool GZJMesh::IsLoginGPU()
	{
		if (VAO != GL_NONE && 
			VBO != GL_NONE && 
			EBO != GL_NONE)
			return true;
		return false;
	}
	
	void GZJMesh::Draw(GZJShaderPtr shader)
	{
		if (!IsLoginGPU())
			LoginGPU();

		// 初始化贴图缓存
		for (int i = 1; i < 32; ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		};

		// todo 加载贴图
		GZJTexturePtr texture = nullptr;
		int diffuseNum = 1;
		int specularNum = 1;
		int bumpNum = 1;
		for (int idx = 0; idx < textures.size(); ++idx)
		{
			glActiveTexture(GL_TEXTURE1 + idx);
			texture = textures[idx];
			if (texture->GetState() == LOADED )
				// 保证已经Load 同时 texturen不为0
			{
				if (!texture->IsLoginGPU())
					texture->LoginGPU();
				ShaderData type = ShaderData::Shader_None;
				if (diffuseNum <= MAX_MATERIAL and texture->GetType() == Texture_Diffuse)
				{
					type = Mate_DiffuseTexture, diffuseNum++;
					shader->SetBool(Mate_Flag_DiffuseTextureUse, true);
				}
				else if (specularNum <= MAX_MATERIAL and texture->GetType() == Texture_Specular)
				{
					type = Mate_SpecularTexture, specularNum++;
					shader->SetBool(Mate_Flag_SpecularTextureUse, true);
				}
				else if (bumpNum <= MAX_MATERIAL and texture->GetType() == Texture_Bump)
				{
					type = Mate_BumpTexture, bumpNum++;
					shader->SetBool(Mate_Flag_NormalTextureUse, true);
				}

				if (type != ShaderData::Shader_None)
				{
					shader->SetInt(type, idx+1);
					glBindTexture(GL_TEXTURE_2D, texture->GetID());
				}
			}
		}

		// 临时处理材质颜色
		if (diffuseNum <= 1)
		{
			shader->SetBool(Mate_Flag_DiffuseTextureUse, false);
			shader->SetVector3(Mate_DiffuseColor, diffuseColor);
		}
		else if (specularNum <= 1)
		{
			shader->SetBool(Mate_Flag_SpecularTextureUse, false);
			shader->SetVector3(Mate_SpecularColor, specularColor);
		}
		else if (bumpNum <= 1)
			shader->SetBool(Mate_Flag_NormalTextureUse, false);

		// 设置放光系数
		shader->SetInt(Mate_Shininess, 32);

		// 渲染
		//std::cout << "state:" << shader->GetState() << " " << VAO <<  std::endl;
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 渲染完把ActiveTexture重置
		glActiveTexture(GL_TEXTURE0);
	}
}
