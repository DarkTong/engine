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
		// ����
		/** id
		*/
		unsigned int id;

		/** ����
		*/
		TextureType type;

		/** ���
		*/
		int width;

		/** �߶�
		*/
		int height;

		/** ��ɫͨ������
		*/
		int nrComponents;

		/** ͼƬ����
		*/
		unsigned char* imageData;

		/** �����ʽ
		*/
		GLenum format;

		/** �Ƿ����ý�������
		*/
		bool isMinMap;

	private:
		// �̳�
		// ���ڽӿ�
		void DoLoad();

		void DoUnLoad();

	public:
		// ����ӿ�

		unsigned int GetID();

		unsigned int GetType();

		ResourceType GetResType();
	};
}


#endif // !__GZJ_TEXTURE_
