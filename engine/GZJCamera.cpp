#include "GZJCamera.h"

namespace GZJ_ENGINE {
	const String CameraParam::Position = "Position";
	const String CameraParam::Rotation = "Rotation";

	GZJCamera::GZJCamera()
	{
		moveCmp = MakeShared<GZJMove>(&transform);
		moveCmp->BindEvent();

		projectionAngle = 45.0f;
		nearPlane = 0.1f;
		farPlane = 100.0f;

		Update();
	}

	Vector4x4 GZJCamera::LookAt()
	{
		//Update();
		//return viewMatrix;
		return transform.GetMatrix(LookAtMatrix);
	}

	Vector4x4 GZJCamera::Projection()
	{
		Vector2 size = GZJWindow::GetInstance()->GetSize();
		return glm::perspective(glm::radians(projectionAngle),
			size.x / size.y, nearPlane, farPlane);
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
			std::cout << "GZJCamera ÉèÖÃ²ÎÊý´íÎó£¡" << std::endl;
			assert(false);
		}
	}

	void GZJCamera::Update()
	{
	}

	void GZJCamera::ParseData(TiXmlElement * ele)
	{
		TiXmlElement * tran_ele = ele->FirstChildElement("transform");
		transform.SetVector3(Position, GZJTools::ParseVector3(tran_ele->FirstChildElement("position")));
		transform.SetVector3(Rotation, GZJTools::ParseVector3(tran_ele->FirstChildElement("rotation")));

		moveCmp->moveSpeed = atof(ele->FirstChildElement("move_speed")->GetText());
		moveCmp->pitchSpeed = atof(ele->FirstChildElement("pitch_speed")->GetText());
		moveCmp->yawSpeed = atof(ele->FirstChildElement("yaw_speed")->GetText());

		DoParseProjectionData(ele->FirstChildElement("projection"));
	}

	void GZJCamera::DoParseProjectionData(TiXmlElement * ele)
	{
		projectionAngle = atof(ele->FirstChildElement("angle")->GetText());
		nearPlane = atof(ele->FirstChildElement("near_plane")->GetText());
		farPlane = atof(ele->FirstChildElement("far_plane")->GetText());
	}
	
}