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
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0 && type == JUST_FILE_RECUTSION)
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
	float GZJTools::clamp(float & v, const float & lo, const float & hi)
	{
		if (v < lo)
			v = lo;
		else if (v > hi)
			v = hi;
		
		return v;
	}
	Vector3 GZJTools::clamp(Vector3 & v, const Vector3 & lo, const Vector3 & hi)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (v[i] < lo[i])
				v[i] = lo[i];
			else if (v[i] > hi[i])
				v[i] = hi[i];
		}
		return v;
	}
	Vector3 GZJTools::ParseVector3(TiXmlElement * node)
	{
		return Vector3(atof(node->Attribute("x")),
			atof(node->Attribute("y")),
			atof(node->Attribute("z")));
	}
}
