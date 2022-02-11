#pragma once
#include "TComponent.h"
#include "../../CoreModule/Point3D.h"
#include "../../Core.h"

namespace Raven { namespace Components {
	struct RAVEN_API Transform: TComponent<Transform> {
		Core::Point3D position;

		Transform() : position(0) {}
	};
}}
