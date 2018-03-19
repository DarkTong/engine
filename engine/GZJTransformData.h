#pragma once

#include "GZJRequire.h"

namespace GZJ_ENGINE {
	struct TransformData {
		static const String Position;
		static const String Rotation;
		static const String Scale;
		static const String EulerAngles;

		static const String LocalPosition;
		static const String LocalRotation;
		static const String LocalScale;
		static const String LocalEulerAngles;

		static const String Up;
		static const String Front;
		static const String Left;
	};

	const String Position				= "position";
	const String Rotation				= "rotation";
	const String Scale					= "scale";					
	const String EulerAngles			= "eulerAngles";

	const String LocalPosition			= "localPosition";
	const String LocalRotation			= "localRotation";
	const String LocalScale				= "localScale";
	const String LocalEulerAngles		= "localEulerAngles";

	const String Up						= "up";
	const String Front					= "front";
	const String Left					= "left";
}