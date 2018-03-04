#include "GZJRequire.h"

namespace GZJ_ENGINE {
	typedef std::vector<String> FileNames;

	enum ReadDirType {
		/** ֻ��ȡ��ǰĿ¼�µ��ļ���������Ŀ¼
		*/
		JUST_FILE,
		/** �ݹ�ض�ȡ��ǰĿ¼�¼���Ŀ¼�µ������ļ�����������Ŀ¼
		*/
		JUST_FILE_RECUTSION,
	};

	class GZJTools {
	public:
		/** ��ȡĿ¼�µ������ļ����ļ���
		@param ��ѯ��Ľ��
		@param �Ѳ����ʼĿ¼
		@param ��ȡ��ʽ
		*/
		static void GetAllFileName(FileNames& files, const String& path, ReadDirType type);
	};
}

