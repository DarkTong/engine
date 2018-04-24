#ifndef _GZJ_TOOLS_
#define _GZJ_TOOLS_

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

		/** clamp����ʱʵ��
		*/
		static float clamp(float& v, const float& lo, const float& hi);
		static Vector3 clamp(Vector3& v, const Vector3& lo, const Vector3& hi);

	};
}
#endif // !_GZJ_TOOLS
