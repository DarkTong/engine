#include "GZJTransform.h"

namespace GZJ_ENGINE{
	const Vector3 GZJTransform::ZERO		= Vector3(0.0f, 0.0f, 0.0f);
	const Vector3 GZJTransform::ONE			= Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 GZJTransform::FRONT		= Vector3(0.0f, 0.0f, 1.0f);
	const Vector3 GZJTransform::LEFT		= Vector3(1.0f, 0.0f, 0.0f);
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
		_left				= LEFT;
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
		case Left:
			_left = data;
			break;
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
		case Left:
			return _left;
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
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.x), LEFT);
		LocalToWorldMatrix =
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.z), FRONT);
		LocalToWorldMatrix =
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.y), UP);
		LocalToWorldMatrix = glm::scale(LocalToWorldMatrix, _scale);
	}
}