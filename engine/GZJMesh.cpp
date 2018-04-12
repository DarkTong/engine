#include "GZJMesh.h"

namespace GZJ_ENGINE {
	GZJMesh::GZJMesh(GZJResourceManager* manager, const String & name
		, ResourceHandle handle)
		:GZJResource(manager, name, handle)
	{
		
		// ��ʱ����
		_path = manager->GetResRoot() + "\\" + name;
		SetState(ResState::UNPREPARE);
	}

	GZJMesh::~GZJMesh()
	{
		UnLoad();
		// �ͷ���ͼ��Դ
		GZJTextureManagerPtr textureMgr = GZJTextureManager::GetInstance();
		for (int idx = 0; idx < textures.size(); ++idx)
			textureMgr->UnLoadByName(textures[idx]);
	}

	void GZJMesh::Prepare(Vertices ver, Indices ind, Textures tex)
	{
		vertices = ver;
		indices = ind;
		textures = tex;
		GZJTextureManagerPtr textureMgr = GZJTextureManager::GetInstance();
		// ������ͼ
		for (int idx = 0; idx < textures.size(); ++idx)
			textureMgr->FindResByName(textures[idx])->SyncLoad();

		cout << "����Դ�Ĵ�С:" << endl;
		cout << "vector:" << vertices.size() << endl;
		cout << "indices:" << indices.size() << endl;
		cout << "textures:" << textures.size() << endl;
		SetState(UNLOAD);
	}

	void GZJMesh::DoLoad()
	{
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

		// ����λ��
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		// ����
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		// ��ͼλ��
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

		glBindVertexArray(0);
	}
	
	void GZJMesh::DoUnLoad()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &VBO);
	}
	
	void GZJMesh::Draw(GZJShaderPtr shader)
	{
		if (GetState() == ResState::LOADED) {

			// todo ������ͼ
			GZJTextureManagerPtr textureMgr = GZJTextureManager::GetInstance();
			GZJTexturePtr texture = nullptr;
			int diffuseNum = 1;
			int specularNum = 1;
			for (int idx = 0; idx < textures.size(); ++idx)
			{
				glActiveTexture(GL_TEXTURE0 + idx);
				texture = std::static_pointer_cast<GZJTexture>(
					textureMgr->FindResByName(textures[idx]));
				if (texture->GetState() == LOADED and texture->GetID())
					// ��֤�Ѿ�Load ͬʱ texturen��Ϊ0
				{
					String name = "";
					if (texture->GetType() == Texture_Diffuse)
						name = "texture_diffuse" + std::to_string(diffuseNum++);
					else if (texture->GetType() == Texture_Specular)
						name = "texture_specular" + std::to_string(specularNum++);

					if (name != "")
					{
						shader->SetInt(name, idx);
						glBindTexture(GL_TEXTURE_2D, texture->GetID());
					}
				}

			}

			// ��Ⱦ
			//std::cout << "state:" << shader->GetState() << " " << VAO <<  std::endl;
			shader->Use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// ��Ⱦ���ActiveTexture����
			glActiveTexture(GL_TEXTURE0);
		}
		else{
			std::cout << "Mesh Resource is not Loaded!!!" << std::endl;
			assert(false);
		}
	}
	ResourceType GZJMesh::GetResType()
	{
		return Mesh;
	}
}
