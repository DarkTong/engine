#include "GZJModel.h"

namespace GZJ_ENGINE {
	GZJModel::GZJModel(GZJResourceManager* manager, const String & name, ResourceHandle handle)
		:GZJResource(manager, name, handle)
	{
		_direction = manager->GetResRoot() + "\\" + name;
		_path = manager->GetResRoot() + "\\" + name + "\\" + name + ".obj";
		SetState(ResState::UNLOAD);
	}

	void GZJModel::DoLoad()
	{
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			return;
		}

		ProcessNode(scene->mRootNode, scene);
	}

	void GZJModel::DoUnLoad()
	{
		GZJMeshPtr mesh;
		while (!meshs.empty())
		{
			mesh = meshs.back();
			mesh->LogoutGPU();
			meshs.pop_back();
		}
	}

	void GZJModel::Draw(const GZJShaderPtr& shader)
	{
		if (GetState() == LOADED)
		{
			if (shader == nullptr)
			{
				std::cout << "没有设置shader程序，请使用SetShader!!" << std::endl;
				ERROR;
			}
			for (auto it = meshs.begin(); it != meshs.end(); ++it)
			{
				(*it)->Draw(shader);
			}
		}
	}

	void GZJModel::ProcessNode(aiNode * node, const aiScene * scene)
	{
		// 处理节点所有的网格（如果有的话）
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *aimesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(aimesh, scene);
		}
		// 接下来对它的子节点重复这一过程
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void GZJModel::ProcessMesh(aiMesh * aimesh, const aiScene * scene)
	{
		meshs.push_back(MakeShared<GZJMesh>());
		auto mesh = meshs.rbegin();

		Vertices &vertices = (*mesh)->vertices;
		Indices &indices = (*mesh)->indices;
		Textures &textures = (*mesh)->textures;

		// 处理定点数据
		for (unsigned int i = 0; i < aimesh->mNumVertices; i++)
		{
			Vertex vertex;
			vertex.position = Vector3(aimesh->mVertices[i].x,
				aimesh->mVertices[i].y, aimesh->mVertices[i].z);
			
			vertex.normal = Vector3(aimesh->mNormals[i].x,
				aimesh->mNormals[i].y, aimesh->mNormals[i].z);

			vertex.texCoords = Vector2(aimesh->mTextureCoords[0][i].x,
				aimesh->mTextureCoords[0][i].y);


			vertices.push_back(vertex);
		}

		// 处理定点索引数据
		for (unsigned int i = 0; i < aimesh->mNumFaces; i++)
		{
			aiFace face = aimesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// 处理材质
		if (aimesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

			Textures texture_diffuse = LoadMaterialTextures(material,
					aiTextureType_DIFFUSE, Texture_Diffuse);
			textures.insert(textures.end(), texture_diffuse.begin(), texture_diffuse.end());

			Textures texture_specular = LoadMaterialTextures(material,
					aiTextureType_SPECULAR, Texture_Specular);
			textures.insert(textures.end(), texture_specular.begin(), texture_specular.end());
		}

	}
	
	ResourceType GZJModel::GetResType()
	{
		return Model;
	}

	Textures GZJModel::LoadMaterialTextures(aiMaterial * material, aiTextureType ai_type, TextureType type)
	{
		Textures textures;
		GZJTextureManagerPtr textureMgr = GZJTextureManager::GetInstance();
		for (unsigned int idx = 0; idx < material->GetTextureCount(ai_type); ++idx)
		{
			aiString str;
			String name;
			GZJTexturePtr texPtr;
			material->GetTexture(ai_type, idx, &str);
			name = _direction + "//" + String(str.C_Str());
			texPtr = std::static_pointer_cast<GZJTexture>(
				textureMgr->FindResByName(name));
			texPtr->Prepare();
			texPtr->SyncLoad();
			texPtr->SetType(type);
			textures.push_back(texPtr);
		}
		return textures;
	}

}

