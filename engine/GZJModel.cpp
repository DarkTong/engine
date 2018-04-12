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
		meshMgr.UnLoadAll();
	}

	void GZJModel::Draw()
	{
		if (GetState() == LOADED)
		{
			if (shader == nullptr)
			{
				std::cout << "没有设置shader程序，请使用SetShader!!" << std::endl;
				ERROR;
			}
			SetShaderData();
			shader->Use();
			meshMgr.DrawAll(shader);
		}
	}

	void GZJModel::SetShader(GZJShaderPtr shader)
	{
		dataVec1.clear();
		dataVec2.clear();
		dataVec3.clear();
		dataMat4.clear();
		this->shader = shader;

		// 设置内部默认设置的数据
		SetMat4(Shader_LocalToWorld, transform.GetMatrix(LocalToWorld));
	}

	void GZJModel::SetShaderData()
	{
		unsigned int tloc = 0;
		// vec1参数
		for (auto it = dataVec1.begin(); it != dataVec1.end(); ++it)
		{
			tloc = glGetUniformLocation(shader->GetShaderID(),
				ShaderDataStr[it->first].c_str());
			glUniform1f(tloc, it->second);
		}
		// vec2参数
		for (auto it = dataVec2.begin(); it != dataVec2.end(); ++it)
		{
			tloc = glGetUniformLocation(shader->GetShaderID(),
				ShaderDataStr[it->first].c_str());
			glUniform2fv(tloc, 1, glm::value_ptr(it->second));
		}
		// vec3参数
		for (auto it = dataVec3.begin(); it != dataVec3.end(); ++it)
		{
			tloc = glGetUniformLocation(shader->GetShaderID(),
				ShaderDataStr[it->first].c_str());
			glUniform3fv(tloc, 1, glm::value_ptr(it->second));
		}
		// mat4参数
		for (auto it = dataMat4.begin(); it != dataMat4.end(); ++it)
		{
			//tloc = glGetUniformLocation(shader->GetShaderID(),
			//	ShaderDataStr[it->first].c_str());
			//glUniformMatrix4fv(tloc, 1, GL_FALSE, glm::value_ptr(it->second));
			shader->SetMatrix(static_cast<ShaderData>(it->first), it->second);
		}
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
		GZJMeshPtr meshPtr = std::static_pointer_cast<GZJMesh>(meshMgr.CreateRes(_name + std::to_string(handle)));

		Vertices vertices;
		Indices indices;
		Textures textures;

		// 处理定点数据
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

		// 处理定点索引数据
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// 处理材质
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			Textures texture_diffuse = LoadMaterialTextures(material,
					aiTextureType_DIFFUSE, Texture_Diffuse);
			textures.insert(textures.end(), texture_diffuse.begin(), texture_diffuse.end());

			Textures texture_specular = LoadMaterialTextures(material,
					aiTextureType_SPECULAR, Texture_Specular);
			textures.insert(textures.end(), texture_specular.begin(), texture_specular.end());
		}

		meshPtr->Prepare(vertices, indices, textures);
		meshPtr->SyncLoad();
	}
	
	void GZJModel::SetVec1(ShaderData shaderData, const float& vec1)
	{
		switch (shaderData) {
		default:
			std::cout << "SetVec1 不能设置参数：" << shaderData << std::endl;
			ERROR;
		}
	}
	void GZJModel::SetVec2(ShaderData shaderData, const Vector2& vec2)
	{
		switch (shaderData) {
		default:
			std::cout << "SetVec2 不能设置参数：" << shaderData << std::endl;
			ERROR;
		}
	}
	void GZJModel::SetVec3(ShaderData shaderData, const Vector3& vec3)
	{
		switch (shaderData) {
		default:
			std::cout << "SetVec3 不能设置参数：" << shaderData << std::endl;
			ERROR;
		}
	}
	void GZJModel::SetMat4(ShaderData shaderData, const Vector4x4& mat4)
	{
		switch (shaderData) {
		case ShaderData::Transform:
			//DoTransform(mat4);
			break;
		case Shader_LocalToWorld:
			break;
		default:
			std::cout << "SetMat4 不能设置参数：" << shaderData << std::endl;
			ERROR;
		}

		auto it = dataMat4.find(shaderData);
		if(it == dataMat4.end())
			dataMat4[shaderData] = Vector4x4(mat4);
		else
			dataMat4[shaderData] = mat4;
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
			material->GetTexture(ai_type, idx, &str);
			name = _direction + "//" + String(str.C_Str());
			textureMgr->CreateRes(name);
			textures.push_back(name);
		}
		return textures;
	}

	//void GZJModel::DoTransform(Vector4x4 mat4)
	//{
	//	// 写数据到对应的参数内
	//	auto it = dataMat4.find(ShaderData::Transform);
	//	if (it == dataMat4.end())
	//		dataMat4.insert(Pair<unsigned int, Vector4x4>(Transform, mat4));
	//	else
	//		dataMat4[ShaderData::Transform] = mat4;
	//}
}

