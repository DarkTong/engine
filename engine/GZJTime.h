#include "GZJRequire.h"

namespace GZJ_ENGINE {
	class GZJTime {
	public:
		static GZJTimePtr _instance;
		static GZJTimePtr GetInstance() {
			if (_instance == nullptr)
				_instance = (GZJTimePtr)new GZJTime();
			return _instance;
		}
	
	public:
		DWORD now_time;

	public:
		GZJTime();

		DWORD GetTickCount();

		void Update();

	};
}