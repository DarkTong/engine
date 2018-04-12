#define STB_IMAGE_IMPLEMENTATION
#include "GZJTexture.h"

namespace GZJ_ENGINE {

	GZJTexture::GZJTexture(GZJResourceManager * mgr, const String & name, ResourceHandle handle)
		:GZJResource(mgr, name, handle)
	{
		width = height = nrComponents = -1;
		imageData = nullptr;
		// 临时，由于贴图资源所在位置和其他资源有些区别
		_path = name;
		id = GL_NONE;
		SetState(UNLOAD);
		isMinMap = false;
	}

	GZJTexture::~GZJTexture()
	{
		UnLoad();
	}

	void GZJTexture::DoLoad()
	{
		if (id != GL_NONE)
		{
			cout << ("Texture is not be UnLoad!!!") << endl;
			return;
		}

		glGenTextures(1, &id);

		imageData = stbi_load(_path.c_str(), &width, &height, &nrComponents, 0);

		if (imageData)
		{
			if (nrComponents == STBI_rgb)
				format = GL_RGB;
			else if (nrComponents == STBI_rgb_alpha)
				format = GL_RGBA;
			else if (nrComponents == STBI_grey)
				format = GL_RED;

			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
			if (isMinMap)
				glGenerateMipmap(GL_TEXTURE_2D);

			/** 临时设置参数，后面通过函数调整
			*/
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if (isMinMap)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			else
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(imageData);
			imageData = nullptr;
		}
		else
		{
			cout << "Texture failed to load at path:" << _path << endl;
			stbi_image_free(imageData);
			imageData = nullptr;

			throw "Load Texture Resoruce Fail!!!";
		}
	}

	void GZJTexture::DoUnLoad()
	{
		glDeleteTextures(1, &id);
		cout << "free texture id:" << id << endl;
		id = GL_NONE;
	}

	unsigned int GZJTexture::GetID()
	{
		return id;
	}

	unsigned int GZJTexture::GetType()
	{
		return type;
	}

	ResourceType GZJTexture::GetResType()
	{
		return Texture;
	}

}

