#include "GZJRequire.h"
#include "GZJResource.h"

namespace GZJ_ENGINE {
	typedef HashMap<String, GZJResourcePtr> ResourceMap;
	typedef Map<ResourceHandle, GZJResourcePtr> ResourceHandleMap;
	typedef ResourceMap::iterator ResourceMapIterator;

	class GZJResourceManager {
	public:
		GZJResourceManager(const String& resRoot);
		virtual ~GZJResourceManager()=0;
	protected:
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
		/** ������Դ
		@param ��Դ����
		@param ��Դ���·��
		*/
		GZJResourcePtr CreateRes(const String& name, const String& path);
		/** �����ֲ�����Դ
		@param ��Դ������
		@return û�з���nullptr
		*/
		GZJResourcePtr FindResByName(const String& name);
		/** ����������Դ
		*/
		void LoadAll();
		/** ���ض�Ӧ���ֵ���Դ
		*/
		void LoadByName(const String& name);
		/** ж��������Դ
		*/
		void UnLoadAll();
		/** ж�ض�Ӧ���ֵ���Դ
		*/
		void UnLoadByName(const String& name);

	private:
		// ���ڽӿ�
		virtual GZJResourcePtr createImp(const String& name, const String& path) = 0;

	};
}
