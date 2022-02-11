#pragma once
#include "TComponent.h"
#include "../../CoreModule/Point3D.h"
#include "../../Core.h"

namespace Raven { namespace Components {
	struct RAVEN_API SpriteRenderer : TComponent<SpriteRenderer> {
		std::string spriteRef;
		explicit SpriteRenderer(std::string& spriteRef): spriteRef(std::move(spriteRef)) {}
	};
}}