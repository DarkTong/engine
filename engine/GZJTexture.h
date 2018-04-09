#ifndef __GZJ_TEXTURE_
#define __GZJ_TEXTURE_

#include "stb_image.h"

#include "GZJRequire.h"
#include "GZJResource.h"
#include "GZJTextureManager.h"

namespace GZJ_ENGINE {
	enum TextureType {
		Texture_Diffuse,
		Texture_Specular,
	};

	class GZJTexture :public GZJResource
	{
	public:
		GZJTexture(GZJResourceManager* mgr, const String& path, ResourceHandle handle);
		~GZJTexture();

	private:
		// 数据
		/** id
		*/
		unsigned int id;

		/** 类型
		*/
		TextureType type;

		/** 宽度
		*/
		int width;

		/** 高度
		*/
		int height;

		/** 颜色通道个数
		*/
		int nrComponents;

		/** 图片数据
		*/
		unsigned char* imageData;

		/** 纹理格式
		*/
		GLenum format;

		/** 是否设置渐进纹理
		*/
		bool isMinMap;

	public:
		// 继承
		void Load();

		void Unload();

	public:
		// 对外接口

		unsigned int GetID();

		unsigned int GetType();
	};
}


#endif // !__GZJ_TEXTURE_
