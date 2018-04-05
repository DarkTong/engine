#include "GZJMove.h"

namespace GZJ_ENGINE {

	void GZJMove::BindEvent()
	{
		eventHandles = {
			EV_Press_KeyBoard,
			EV_Press_Mouse,
		};

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
	}

	void GZJMove::SetVector3(const MoveData& param)
	{
		Vector3 pos = transform->GetVector3(Position);
		Vector3 rot = transform->GetVector3(Rotation);
		Vector3 dir;
		Vector3 rotDegree;
		if (param == MOVE_FRONT) 
		{
			dir = transform->GetVector3(WorldFront);
		}
		else if (param == MOVE_LEFT)
		{
			dir = transform->GetVector3(WorldRight);
		}
		else if (param == MOVE_UP)
		{
			dir = transform->GetVector3(Up);
		}
		else if (param == MOVE_BACK)
		{
			dir = transform->GetVector3(WorldFront);
			dir = dir * -1.0f;
		}
		else if (param == MOVE_RIGHT)
		{
			dir = transform->GetVector3(WorldRight);
			dir = dir * -1.0f;
		}
		else if (param == MOVE_DOWN)
		{
			dir = transform->GetVector3(Up);
			dir = dir * -1.0f;
		}
		else if (param == MOVE_YAW)
		{
			rotDegree.y += -1.0f * xOffset * yawSpeed;
		}
		else if (param == MOVE_PITCH)
		{
			rotDegree.x += yOffset * pitchSpeed;
		}
		pos = pos + dir * moveSpeed;
		cout << "rotDegree:" << showV3(rotDegree) << endl;
		cout << "rot:" << showV3(rot) << endl;
		rot = rot + rotDegree;
		transform->SetVector3(Position, pos);
		transform->SetVector3(Rotation, rot);
	}

	void GZJMove::LogicUpdate()
	{
		UpdateTransform();
		UpdateCursor();
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
			tmp = transform->GetVector3(Position);
			cout << "pos:" << showV3(tmp) << endl;
			//tmp = transform->GetVector3(WorldFront);
			//cout << "worldFront:" << showV3(tmp) << endl;
			//tmp = transform->GetVector3(WorldUp);
			//cout << "worldUp:" << showV3(tmp) << endl;
			//tmp = transform->GetVector3(WorldRight);
			//cout << "worldRight:" << showV3(tmp) << endl;

		}
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

				cout << "offset:" << xOffset << " " << yOffset << endl;
				cout << "rot:" << showV3(transform->GetVector3(Rotation)) << endl;
			}
		}

		xPos = pos.x;
		yPos = pos.y;
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
