#include "GZJRender.h"

#include <vector>

namespace GZJ_ENGINE {
	class GZJRenderStatic : public GZJRender{
	public:
		static GZJRenderStaticPtr _instance;
		static GZJRenderStaticPtr GetInstance() {
			if (_instance == nullptr)
				_instance = (GZJRenderStaticPtr) new GZJRenderStatic();
			return _instance;
		}
	private:
		std::vector<RenderUtil> renderDatas;
		

	public:
		
		void PrepareRender();

		void Do_PrepareRender(RenderUtil& data);

		void Render();

		void AddRenderData(const RenderUtil& data);

		void ClearRenderDatas();
	};
}
