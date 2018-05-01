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
		Texture_Bump,
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

	private:
		// 继承
		// 对内接口
		void DoLoad();

		void DoUnLoad();

	public:
		// 对外接口

		unsigned int GetID();

		unsigned int GetType();

		void SetType(TextureType type)
		{
			this->type = type;
		}

		ResourceType GetResType();

		/** 资源加载进GPU
		*/
		void LoginGPU();

		/** 资源从GPU中卸载
		*/
		void LogoutGPU();

		/** 资源是加载进GPU
		*/
		bool IsLoginGPU();
	};
}


#endif // !__GZJ_TEXTURE_
