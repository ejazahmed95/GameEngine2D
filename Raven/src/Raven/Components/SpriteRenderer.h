#pragma once
#include "TComponent.h"
#include "../CoreModule/Point3D.h"
#include "../Core.h"

namespace Raven { namespace Components {
	struct RAVEN_API SpriteRenderer : public TComponent<SpriteRenderer> {
		std::string spriteRef;
		explicit SpriteRenderer(std::string& spriteRef): spriteRef(std::move(spriteRef)) {}

		static void from_json(const json& j, SpriteRenderer& sr) {
			j.at("spriteRef").get_to(sr.spriteRef);
		}
	};
}}