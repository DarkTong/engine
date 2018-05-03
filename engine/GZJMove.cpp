#include "GZJMove.h"

namespace GZJ_ENGINE {
	GZJMove::GZJMove(GZJTransform * transform, float moveSpeed, 
		float yawSpeed, float pitchSpeed)
		:transform(transform), moveSpeed(moveSpeed)
		, yawSpeed(yawSpeed), pitchSpeed(pitchSpeed)
	{
		autoRowYaw = autoRowPitch = false;

		eventHandles = { EV_Login_Update };
		GZJEventSystem::GetInstance()->Bind(reinterpret_cast<TargetID>(this)
			, EV_Login_Update
			, NormalDelegate(this, &GZJMove::LogicUpdate));
	}
	GZJMove::~GZJMove()
	{
		UnBindEvent();
	}
	void GZJMove::BindEvent()
	{
		eventHandles.push_back(EV_Press_KeyBoard);
		eventHandles.push_back(EV_Press_Mouse);

		GZJEventSystem::GetInstance()->Bind(reinterpret_cast<TargetID>(this)
			, EV_Press_KeyBoard
			, NormalDelegate(this, &GZJMove::Handle_Press_KeyBoard));
		GZJEventSystem::GetInstance()->Bind(reinterpret_cast<TargetID>(this),
			EV_Press_Mouse,
			NormalDelegate(this, &GZJMove::Handle_Press_Mouse));
	}

	void GZJMove::UnBindEvent()
	{
		for (auto it = eventHandles.begin(); it != eventHandles.end(); ++it)
		{
			GZJEventSystem::GetInstance()->UnBind(reinterpret_cast<TargetID>(this)
				, *it);
		}
		eventHandles.clear();
	}

	void GZJMove::SetVector3(const MoveData& param)
	{
		Vector3 pos = transform->GetVector3(Position);
		Vector3 rot = transform->GetVector3(Rotation);
		Vector3 dir;
		Vector3 rotDegree;
		if (param == MOVE_FRONT) 
		{
			dir = transform->GetVector3(Front);
		}
		else if (param == MOVE_LEFT)
		{
			dir = transform->GetVector3(Right);
		}
		else if (param == MOVE_UP)
		{
			dir = transform->GetVector3(Up);
		}
		else if (param == MOVE_BACK)
		{
			dir = transform->GetVector3(Front);
			dir = dir * -1.0f;
		}
		else if (param == MOVE_RIGHT)
		{
			dir = transform->GetVector3(Right);
			dir = dir * -1.0f;
		}
		else if (param == MOVE_DOWN)
		{
			dir = transform->GetVector3(Up);
			dir = dir * -1.0f;
		}
		else if (param == MOVE_YAW)
		{
			rotDegree.y += -1.0f * xOffset * yawSpeed * GZJTime::GetInstance()->frame_time;
		}
		else if (param == MOVE_PITCH)
		{
			rotDegree.x += yOffset * pitchSpeed * GZJTime::GetInstance()->frame_time;
			if (rot.x + rotDegree.x > 80.0f || rot.x + rotDegree.x < -80.0f)
				rotDegree.x = 0.000f;
		}
		pos = pos + dir * moveSpeed * GZJTime::GetInstance()->frame_time;
		//cout << "rotDegree:" << showV3(rotDegree) << endl;
		//cout << "rot:" << showV3(rot) << endl;
		rot = rot + rotDegree;
		transform->SetVector3(Position, pos);
		transform->SetVector3(Rotation, rot);
		//cout << "rotation:" << showV3(transform->GetVector3(Rotation)) << endl;
		//cout << "front:" << showV3(transform->GetVector3(Front)) << endl;
	}

	void GZJMove::LogicUpdate(const GZJEventParamObj& param)
	{
		AutoTransform();
		UpdateTransform();
		UpdateCursor();
	}

	void GZJMove::DoParseData(TiXmlElement * ele)
	{
		TiXmlElement* child;

		child = ele->FirstChildElement("yaw_speed");
		yawSpeed = !child ? 0.0 : (float)atof(ele->FirstChildElement("yaw_speed")
				->GetText());
			
		child = ele->FirstChildElement("pitch_speed");
		pitchSpeed = !child ? 0.0 : (float)atof(ele->FirstChildElement("pitch_speed")
			->GetText());

		child = ele->FirstChildElement("move_speed");
		moveSpeed = !child ? 0.0 : (float)atof(ele->FirstChildElement("move_speed")
			->GetText());

		child = ele->FirstChildElement("auto_row_yaw");
		if (child && String(child->GetText()) == "true")
			autoRowYaw = true;
	}

	void GZJMove::ParseData(TiXmlElement * ele)
	{
		if (ele != nullptr)
			DoParseData(ele);
		else
			cout << "GZJMove ParseData, ele is nullptr!" << endl;
	}

	void GZJMove::UpdateTransform()
	{
		for (auto it = keyIsPress.begin(); it != keyIsPress.end(); ++it)
		{
			if (!it->second) continue;

			switch (it->first) {
			case GLFW_KEY_W:
				SetVector3(MOVE_FRONT);
				break;
			case GLFW_KEY_A:
				SetVector3(MOVE_LEFT);
				break;
			case GLFW_KEY_S:
				SetVector3(MOVE_BACK);
				break;
			case GLFW_KEY_D:
				SetVector3(MOVE_RIGHT);
				break;
			case GLFW_KEY_SPACE:
				SetVector3(MOVE_UP);
				break;
			case GLFW_KEY_LEFT_SHIFT:
				SetVector3(MOVE_DOWN);
				break;
			case  GLFW_MOUSE_BUTTON_LEFT:
				SetVector3(MOVE_YAW);
				SetVector3(MOVE_PITCH);
				break;
			default:
				break;
			}

			Vector3 tmp;
			//tmp = transform->GetVector3(Position);
			//cout << "pos:" << showV3(tmp) << endl;
			//tmp = transform->GetVector3(Front);
			//cout << "worldFront:" << showV3(tmp) << endl;
			//tmp = transform->GetVector3(Up);
			//cout << "worldUp:" << showV3(tmp) << endl;
			//tmp = transform->GetVector3(Right);
			//cout << "worldRight:" << showV3(tmp) << endl;

		}
	}

	void GZJMove::AutoTransform()
	{
		if (autoRowYaw) UpdateData(MOVE_YAW, 1.0f);
		if (autoRowPitch) UpdateData(MOVE_PITCH, 1.0f);
	}

	void GZJMove::UpdateCursor()
	{
		Vector2 pos = GZJWindow::GetInstance()->GetCursorPos();

		for (auto it = cursorIsPress.begin(); it != cursorIsPress.end(); ++it)
		{
			if (!it->second)
				continue;

			if (it->first == GLFW_MOUSE_BUTTON_LEFT)
			{
				xOffset = pos.x - xPos;
				yOffset = pos.y - yPos;
				SetVector3(MOVE_YAW);
				SetVector3(MOVE_PITCH);

				//cout << "offset:" << xOffset << " " << yOffset << endl;
				//cout << "rot:" << showV3(transform->GetVector3(Rotation)) << endl;
			}
		}

		xPos = pos.x;
		yPos = pos.y;
	}

	void GZJMove::UpdateData(const MoveData & param, float offset)
	{
		bool flag = false;
		Vector3 dir;
		switch (param)
		{
		case MOVE_FRONT:
			dir = transform->GetVector3(Front);
			break;
		case MOVE_LEFT:
			dir = transform->GetVector3(Right);
			break;
		case MOVE_UP:
			dir = transform->GetVector3(Up);
		case MOVE_BACK:
			dir = transform->GetVector3(Front) * -1.0f;
			break;
		case MOVE_RIGHT:
			dir = transform->GetVector3(Right) * -1.0f;
			break;
		case MOVE_DOWN:
			dir = transform->GetVector3(Up) * -1.0f;
			break;
		default:
			flag = true;
			break;
		}
		if(!flag)
		{
			Vector3 pos = transform->GetVector3(Position);
			pos += offset * dir * moveSpeed * GZJTime::GetInstance()->frame_time;
			transform->SetVector3(Position, pos);
			return;
		}

		flag = false;
		Vector3 rotDegree;
		switch (param)
		{
		case MOVE_YAW:
			rotDegree.y += offset * yawSpeed * GZJTime::GetInstance()->frame_time;
			if (rotDegree.y > 180.0f) rotDegree.y -= 180.0f;
			break;
		case MOVE_PITCH:
			rotDegree.x += offset * pitchSpeed * GZJTime::GetInstance()->frame_time;
			break;
		default:
			flag = true;
			break;
		}
		if (!flag)
		{
			Vector3 rot = transform->GetVector3(Rotation);
			if (rot.x + rotDegree.x > 80.0f || rot.x + rotDegree.x < -80.0f)
				rotDegree.x = 0.000f;
			rot = rot + rotDegree;
			transform->SetVector3(Rotation, rot);
			return;
		}
	}

	void GZJMove::Handle_Press_KeyBoard(const GZJEventParamObj& param)
	{
		auto p = static_cast<const Param_Press_KeyBoard&>(param);

		if (p.action == GLFW_PRESS || p.action == GLFW_REPEAT)
			keyIsPress[p.key] = true;
		else if (p.action == GLFW_RELEASE)
			keyIsPress[p.key] = false;
	}

	void GZJMove::Handle_Press_Mouse(const GZJEventParamObj& param)
	{
		auto p = static_cast<const Param_Press_Mouse&>(param);

		if (p.key == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (p.action == GLFW_PRESS)
			{
				Vector2 pos = GZJWindow::GetInstance()->GetCursorPos();
				xPos = pos.x;
				yPos = pos.y;

				cursorIsPress[p.key] = true;
			}
			else if (p.action == GLFW_RELEASE)
			{
				cursorIsPress[p.key] = false;
			}
		}
	}

}
