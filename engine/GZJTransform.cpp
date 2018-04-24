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
		_localUp			= UP;
		_localFront			= FRONT;
		_localRight			= RIGHT;

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
		//case Up:
		//	_up = data;
		//	break;
		//case Front:
		//	_front = data;
		//	break;
		//case Right:
		//	_right = data;
		//	break;
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
			return _position;
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
		case LocalUp:
			return _localUp;
		case LocalFront:
			return _localFront;
		case LocalRight:
			return _localRight;
		default:
			std::cout << "GZJTransform GetVector3 参数错误!!!" << std::endl;
			assert(false);
		}
	}
	
	Vector4x4 GZJTransform::GetMatrix(TransformData param) 
	{
		switch (param)
		{
		case TransformData::LocalToWorld:
			return LocalToWorldMatrix;
		case TransformData::LookAtMatrix:
			return glm::lookAt(_position, _position + _front, _up);
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
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.y), UP);
		LocalToWorldMatrix =
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.z), FRONT);
		LocalToWorldMatrix =
			glm::rotate(LocalToWorldMatrix, glm::radians(_rotation.x), RIGHT);

		LocalToWorldMatrix = glm::scale(LocalToWorldMatrix, _scale);

		_up = glm::normalize(Vector3(LocalToWorldMatrix * Vector4(_localUp, 0.0f)));
		_front = glm::normalize(Vector3(LocalToWorldMatrix * Vector4(_localFront, 0.0f)));
		_right = glm::normalize(glm::cross(_up, _front));
		//_right = Vector3(LocalToWorldMatrix * Vector4(_localRight, 0.0f));

		//cout << "_up:" << showV3(_up) << endl;
		//cout << "_front:" << showV3(_front) << endl;
		//cout << "_right:" << showV3(_right) << endl;

		//cout << "_L0" << showV4(LocalToWorldMatrix[0]) << endl;
		//cout << "_L1" << showV4(LocalToWorldMatrix[1]) << endl;
		//cout << "_L2" << showV4(LocalToWorldMatrix[2]) << endl;
		//cout << "_L3" << showV4(LocalToWorldMatrix[3]) << endl;
	}
}