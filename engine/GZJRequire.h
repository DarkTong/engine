#ifndef _GZJ_REQUIRE_
#define _GZJ_REQUIRE_

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FastDelegate.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <io.h> 

namespace GZJ_ENGINE {
	
	/** ʹ��ĳЩ�����ռ��ڵĺ���
	*/
	using std::cout;
	using std::endl;
	using fastdelegate::FastDelegate0;
	using fastdelegate::FastDelegate1;
	using fastdelegate::FastDelegate2;


	//-------- ö�� --------
	/** ��Դ״̬
	*/
	enum ResState {
		UNPREPARE,
		PREPAREING,
		UNLOAD,
		LOADING,
		LOADED,
		OLDED,
	};
	//-------- ������ --------
	/** ��Դ���
	*/
	typedef unsigned long long ResourceHandle;
	
	typedef std::string String;
	template<typename T1, typename T2> using HashMap = std::unordered_map<T1, T2>;
	template<typename T1, typename T2> using Map = std::map<T1, T2>;
	template<typename T> using Set = std::set<T>;
	template<typename T1, typename T2> using Pair = std::pair<T1, T2>;
	typedef glm::vec2 Vector2;
	typedef glm::vec3 Vector3;
	typedef glm::vec4 Vector4;
	typedef glm::mat3 Vector3x3;
	typedef glm::mat4 Vector4x4;

	class GZJTime;
	class GZJWindow;
	class GZJShader;
	class GZJShaderManager;
	class GZJRender;
	class GZJRenderStatic;
	class GZJRenderDynamic;
	class GZJResource;
	class GZJResourceManager;
	class GZJResourceGroupManager;
	class GZJTexture;
	class GZJTextureManager;
	class GZJMesh;
	class GZJMeshManager;
	class GZJModel;
	class GZJModelManager;
	class GZJCamera;
	class GZJMove;
	class GZJEventSystem;
	class GZJEvent;
	class GZJEventParamObj;


	class GZJTools;

	template<typename T> using SharedPtr = std::shared_ptr<T>;
	//template<typename T> using MakeShared = std::make_shared<T>;
	#define MakeShared std::make_shared
	template<typename T> using WeakShared = std::weak_ptr<T>;
// #define SharedPtr std::shared_ptr

	// ����ָ��
	typedef SharedPtr<GZJTime>						GZJTimePtr;
	typedef SharedPtr<GZJWindow>					GZJWindowPtr;
	typedef SharedPtr<GZJShader>					GZJShaderPtr;
	typedef SharedPtr<GZJShaderManager>				GZJShaderManagerPtr;
	typedef SharedPtr<GZJRender>					GZJRenderPtr;
	typedef SharedPtr<GZJRenderStatic>				GZJRenderStaticPtr;
	typedef SharedPtr<GZJRenderDynamic>				GZJRenderDynamicPtr;
	typedef SharedPtr<GZJResource>					GZJResourcePtr;
	typedef SharedPtr<GZJResourceManager>			GZJResourceManagerPtr;
	typedef SharedPtr<GZJResourceGroupManager>		GZJResourceGroupManagerPtr;
	typedef SharedPtr<GZJMesh>						GZJMeshPtr;
	typedef SharedPtr<GZJMeshManager>				GZJMeshManagerPtr;
	typedef SharedPtr<GZJModel>						GZJModelPtr;
	typedef SharedPtr<GZJModelManager>				GZJModelManagerPtr;
	typedef SharedPtr<GZJEventSystem>				GZJEventSystemPtr;
	typedef SharedPtr<GZJEventParamObj>				EventParamObjPtr;

	// typedef
	typedef FastDelegate1<GZJEventParamObj> NormalDelegate;

	// -------- common function --------

	// -------- common value --------
	const String ENGINE_ROOT_PATH		= "F:\\��ҵ���2\\engine";
	const String SHADER_ROOT_PATH		= "\\shader";
	const String ENGINE_SRC_ROOT_PATH	= ENGINE_ROOT_PATH + "\\src";

}

#endif // _GZJ_REQUIRE
