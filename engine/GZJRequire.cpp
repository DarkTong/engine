#include "GZJRequire.h"


// ----------- common function --------------
namespace GZJ_ENGINE {
	String showV3(Vector3 tmp) {
		String str = "";
		str = "(" + std::to_string(tmp.x) + "," + std::to_string(tmp.y) + "," + std::to_string(tmp.z) + ")";
		return str;
	}
	String showV4(Vector4 tmp)
	{
		String str = "";
		str = "(" + std::to_string(tmp.x) + "," + std::to_string(tmp.y) + "," + std::to_string(tmp.z) + "," + std::to_string(tmp.w) + ")";
		return str;
	}
}
