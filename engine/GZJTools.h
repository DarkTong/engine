#include "GZJRequire.h"

namespace GZJ_ENGINE {
	typedef std::vector<String> FileNames;

	enum ReadDirType {
		/** 只读取当前目录下的文件，不包含目录
		*/
		JUST_FILE,
		/** 递归地读取当前目录下及子目录下的所有文件名，不包含目录
		*/
		JUST_FILE_RECUTSION,
	};

	class GZJTools {
	public:
		/** 获取目录下的所有文件的文件名
		@param 查询后的结果
		@param 搜查的起始目录
		@param 读取方式
		*/
		static void GetAllFileName(FileNames& files, const String& path, ReadDirType type);
	};
}

