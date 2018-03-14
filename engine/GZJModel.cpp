#include "GZJModel.h"

namespace GZJ_ENGINE {
	GZJModel::GZJModel(GZJResourceManagerPtr manager, const String & name, ResourceHandle handle)
		:GZJResource(manager, name, handle)
	{
		_path = manager->GetResRoot() + "\\" + name;
		_state = ResState::UNPREPARE;
	}

	void GZJModel::Load()
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

	void GZJModel::Unload()
	{
		meshMgr.UnLoadAll();
	}

	void GZJModel::ProcessNode(aiNode * node, const aiScene * scene)
	{
		// 处理节点所有的网格（如果有的话）
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene);
		}
		// 接下来对它的子节点重复这一过程
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void GZJModel::ProcessMesh(aiMesh * mesh, const aiScene * scene)
	{
		ResourceHandle handle = meshMgr.GetNextHandle();
		GZJMeshPtr meshPtr = std::dynamic_pointer_cast<GZJMesh>(meshMgr.CreateRes(_name + std::to_string(handle)));

		Vertices vertices;
		Indices indices;
		Textures textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vertex.position = Vector3(mesh->mVertices[i].x,
				mesh->mVertices[i].y, mesh->mVertices[i].z);
			
			vertex.normal = Vector3(mesh->mNormals[i].x,
				mesh->mNormals[i].y, mesh->mNormals[i].z);

			vertex.texCoords = Vector2(mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y);


			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		//	// 处理材质
		//  // todo
		//	if (mesh->mMaterialIndex >= 0)
		//	{
		//		...
		//	}

		meshPtr->Prepare(vertices, indices, textures);
	}
}

