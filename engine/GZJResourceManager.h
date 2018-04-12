#ifndef __GZJ_RESOURCE_MANAGER__
#define __GZJ_RESOURCE_MANAGER__

#include "GZJRequire.h"
#include "GZJResource.h"

namespace GZJ_ENGINE {

	typedef HashMap<String, GZJResourcePtr> ResourceMap;
	typedef Map<ResourceHandle, GZJResourcePtr> ResourceHandleMap;
	typedef ResourceMap::iterator ResourceMapIterator;

	class GZJResourceManager {
	public:
		GZJResourceManager();
		~GZJResourceManager();
	protected:
		// /** �������������ָ��
		// */
		// GZJResourceManagerPtr self;
		/** ������Դ���洢��Դ
		*/
		ResourceMap resMap;
		/** ������Դ���������Դ
		*/
		ResourceHandleMap resHandleMap;
		/** ��ǰδ�������Դ���
		*/
		ResourceHandle resHandle;
		/** ��ǰ�������Դ�ĸ�·��
		*/
		String _resRoot;
	public:
		/** ����������
		*/
		virtual void StartUp() = 0;

		/** �رչ�����
		*/
		virtual void ShutDown() = 0;

		/** ������Դ
		@param ��Դ����
		@param ��Դ���·��
		*/
		GZJResourcePtr CreateRes(const String& name);

		/** �����ֲ�����Դ
		@param ��Դ������
		@return û�з���nullptr
		*/
		GZJResourcePtr FindResByName(const String& name);

		/** ׼��������Դ
		*/
		virtual void PrepareAll() = 0;

		/** ����������Դ
		*/
		virtual void LoadAll(bool isAsyncLoad=false);

		/** ���ض�Ӧ���ֵ���Դ
		*/
		virtual void LoadByName(const String& name);

		/** ж��������Դ
		*/
		virtual void UnLoadAll();

		/** ж�ض�Ӧ���ֵ���Դ
		*/
		virtual void UnLoadByName(const String& name);

		/** �ж���Դ�Ƿ��Ѿ�������
		*/
		bool IsLoad(const String& name);

		/** ��ȡ��Դ·��
		@param ��Դ·��
		*/
		String GetResRoot();

		/** ��ȡ��һ����Դ���
		*/
		ResourceHandle GetNextHandle();

		// /** ��ȡ���������ָ��
		// */
		// GZJResourceManagerPtr GetSelf() const;

	protected:
		// ���ڽӿ�
		virtual GZJResource* createImp(const String& name) = 0;

	};
}
#endif // !__GZJ_RESOURCE_MANAGER__
