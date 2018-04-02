#ifndef __GZJ_TEST_
#define __GZJ_TEST_

#include <cstdio>
#include <sstream>
#include "GZJRequire.h"
#include "GZJTransform.h"

namespace GZJ_ENGINE {
	using namespace std;
	class GZJTest {
	public:
		// ²âÊÔTransform
		GZJTransform trans;
		//static const float esp;
		bool InputTransform() {
			using namespace std;
			int type;
			float x, y, z;
			cin >> type >> x >> y >> z;
			Vector3 data = Vector3(x, y, z);
			switch (type) {
			case 1:
				trans.SetVector3(Position, data);
				break;
			case 2:
				trans.SetVector3(Rotation, data);
				break;
			case 3:
				trans.SetVector3(Scale, data);
				break;
			default:
				return false;
			}
			return true;
		}

		void ShowTransform() {
			using namespace std;
			cout << "--_position: " << ShowV3(trans.GetVector3(Position)) << endl;
			cout << "--_rotation: " << ShowV3(trans.GetVector3(Rotation)) << endl;
			cout << "--_scale: " << ShowV3(trans.GetVector3(Scale)) << endl;
			//cout << "--_eulerAngles: " << ShowV3(trans.GetVector3(Position)) << endl;
			//cout << "--_localPosition: " << ShowV3(trans.GetVector3(Position)) << endl;
			//cout << "--_localRotation: " << ShowV3(trans.GetVector3(Position)) << endl;
			//cout << "--_localScale: " << ShowV3(trans.GetVector3(Position)) << endl;
			//cout << "--_localEulerAngles: " << ShowV3(trans.GetVector3(Position)) << endl;
			cout << "--_up: " << ShowV3(trans.GetVector3(Up)) << endl;
			cout << "--_front: " << ShowV3(trans.GetVector3(Front)) << endl;
			cout << "--_right: " << ShowV3(trans.GetVector3(Right)) << endl;
			cout << "--_worldUP: " << ShowV3(trans.GetVector3(WorldUp)) << endl;
		}
		
	public:
		
		// ¹«ÓÐ
		String ShowV3(Vector3 a) {
			
			String str =  "(" + to_string(a.x) + "," + to_string(a.y)
					+ "," + to_string(a.z) + ")\n";
			return str;
		}
	};
	//const float GZJTest::esp = 1e-9f;
}

#endif // !__GZJ_TEST_
