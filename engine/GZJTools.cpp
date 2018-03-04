#include "GZJTools.h"

namespace GZJ_ENGINE {
	void GZJTools::GetAllFileName(FileNames& files, const String& path, ReadDirType type)
	{
		long   hFile = 0;
		//文件信息    
		struct _finddata_t fileinfo;
		std::string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				if ((fileinfo.attrib &  _A_SUBDIR) and type == JUST_FILE_RECUTSION)
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					{
						GetAllFileName(files, p.assign(path).append("\\").append(fileinfo.name), type);
					}
				}
				else
				{
					files.push_back(fileinfo.name);
				}

			} while (_findnext(hFile, &fileinfo) == 0);

			_findclose(hFile);
		}
	}
}
