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
		Vector3 dir;
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
			dir = transform->GetVector3(WorldUp);
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
			dir = transform->GetVector3(WorldUp);
			dir = dir * -1.0f;
		}
		pos = pos + dir * speed;
		transform->SetVector3(Position, pos);
	}

	void GZJMove::Handle_Press_KeyBoard(const GZJEventParamObj& param)
	{
		auto p = static_cast<const Param_Press_KeyBoard&>(param);

		if (p.action == GLFW_PRESS) {
			switch (p.key) {
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

	void GZJMove::Handle_Press_Mouse(const GZJEventParamObj& param)
	{
		auto p = static_cast<const Param_Press_KeyBoard&>(param);
	}

}
