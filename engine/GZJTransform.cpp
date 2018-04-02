#include "GZJTransform.h"

namespace GZJ_ENGINE{
	const Vector3 GZJTransform::ZERO		= Vector3(0.0f, 0.0f, 0.0f);
	const Vector3 GZJTransform::ONE			= Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 GZJTransform::FRONT		= Vector3(0.0f, 0.0f, 1.0f);
	const Vector3 GZJTransform::RIGHT		= Vector3(1.0f, 0.0f, 0.0f);
	const Vector3 GZJTransform::UP			= Vector3(0.0f, 1.0f, 0.0f);
	GZJTransform::GZJTransform()
	{
		_position 			= ZERO;
		_rotation 			= ZERO;
		_scale				= ONE;
		_eulerAngles		= ZERO;
		_localPosition		= ZERO;
		_localRotation		= ZERO;
		_localEulerAngles	= ZERO;
		_up					= UP;
		_front				= FRONT;
		_right				= RIGHT;

		Update();
	}

	GZJTransform::GZJTransform(Vector3 position, Vector3 rotation, Vector3 scale)
	{
	}

	void GZJTransform::SetVector3(TransformData param, Vector3 data)
	{
		switch (param) {
		case Position:
			_position = data;
			Update();
			break;
		case Rotation:
			_rotation = data;
			Update();
			break;
		case Scale:
			_scale = data;
			Update();
			break;
		//case EulerAngles:
		//	_eulerAngles = data;
		//	break;
		//case LocalPosition:
		//	_localPosition = data;
		//	break;
		//case LocalRotation:
		//	_localRotation = data;
		//	break;
		//case LocalScale:
		//	_localScale = data;
		//	break;
		//case LocalEulerAngles:
		//	_localEulerAngles = data;
		//	break;
		case Up:
			_up = data;
			break;
		case Front:
			_front = data;
			break;
		case Right:
			_right = data;
			break;
		default:
			std::cout << "GZJTransform SetVector3 参数错误!!!" << std::endl;
			assert(false);
		}
		//Update();
	}
	
	Vector3 GZJTransform::GetVector3(TransformData param)
	{
		switch (param) {
		case Position:
			return  _position;
		case Rotation:
			return _rotation;
		case Scale:
			return _scale;
		//case EulerAngles:
		//	return _eulerAngles;
		//case LocalPosition:
		//	return _localPosition;
		//case LocalRotation:
		//	return _localRotation;
		//case LocalScale:
		//	return _localScale;
		//case LocalEulerAngles:
		//	return _localEulerAngles;
		case Up:
			return _up;
		case Front:
			return _front;
		case Right:
			return _right;
		case WorldUp:
			return _worldUp;
		case WorldFront:
			return _worldFront;
		default:
			std::cout << "GZJTransform GetVector3 参数错误!!!" << std::endl;
			assert(false);
		}
	}
	
	Vector4x4 GZJTransform::GetMatrix(TransformData param) 
	{
		switch (param)
		{
		case GZJ_ENGINE::LocalToWorld:
			return LocalToWorldMatrix;
		default:
			std::cout << "GZJTransform GetMatrix 参数错误!!!" << std::endl;
			assert(false);
		}
	}

	void GZJTransform::DoScale(Vector3 scale)
	{
		_scale = scale;
	}
	void GZJTransform::DoRotate(Vector3 rotate)
	{
	}
	void GZJTransform::DoTranslate(Vector3 translate)
	{
		_position = translate;
		LocalToWorldMatrix = Vector4x4();

	}
	void GZJTransform::Update()
	{
		LocalToWorldMatrix = Vector4x4();
		LocalToWorldMatrix = glm::translate(LocalToWorldMatrix, _position);
		LocalToWorldMatrix = 
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.x), RIGHT);
		LocalToWorldMatrix =
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.z), FRONT);
		LocalToWorldMatrix =
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.y), UP);
		LocalToWorldMatrix = glm::scale(LocalToWorldMatrix, _scale);

		_worldUp = Vector3(LocalToWorldMatrix * Vector4(_up, 0.0));
		_worldFront = Vector3(LocalToWorldMatrix * Vector4(_front, 0.0));
	}
}