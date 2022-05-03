#include "Transform.h"

namespace Raven { namespace Components {

	void Transform::Translate(Core::Point3D distance) {
		position += distance;
	}

	void Transform::Rotate(Core::Point3D rot) {
		rotation += rot;
	}
}}
