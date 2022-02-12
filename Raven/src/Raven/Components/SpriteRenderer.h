#pragma once
#include "TComponent.h"
#include "../CoreModule/Point3D.h"
#include "../Core.h"

namespace Raven { namespace Components {
	struct RAVEN_API SpriteRenderer : TComponent<SpriteRenderer> {
		std::string m_spriteRef;
		explicit SpriteRenderer(std::string& spriteRef): m_spriteRef(std::move(spriteRef)) {}
	};
}}