#include "GZJCamera.h"

namespace GZJ_ENGINE {
	const String CameraParam::Position = "Position";
	const String CameraParam::Rotation = "Rotation";

	GZJCamera::GZJCamera()
	{
		Update();
	}

	Vector4x4 GZJCamera::LookAt()
	{
		return viewMatrix;
	}

	void GZJCamera::SetVector3(const String param, Vector3 data)
	{
		if(param == CameraParam::Position)
		{
			transform.SetVector3(Position, data);
			Update();
		}
		else if (param == CameraParam::Rotation)
		{
			transform.SetVector3(Rotation, data);
			Update();
		}
		else
		{
			std::cout << "GZJCamera ���ò�������" << std::endl;
			assert(false);
		}
	}

	void GZJCamera::Update()
	{
		// �۲�ռ����
		viewMatrix = glm::lookAt(transform.GetVector3(Position),
			transform.GetVector3(Position) + transform.GetVector3(WorldFront),
			transform.GetVector3(WorldUp));

	}
	
}