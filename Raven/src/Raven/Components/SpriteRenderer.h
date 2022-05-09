#pragma once
#include "TComponent.h"
#include "../CoreModule/Point3D.h"
#include "../Core.h"

namespace Raven { namespace Components {
	struct RAVEN_API SpriteRenderer : public TComponent<SpriteRenderer> {
		std::string spriteRef;
		std::string texName;
		GLib::Sprite* sprite = nullptr;
		Core::Point3D scale = Core::Point3D(1);

		~SpriteRenderer() {
			if(sprite != nullptr) {
				GLib::Release(sprite);
			}
		}
		explicit SpriteRenderer(std::string& spriteRef): spriteRef(std::move(spriteRef)) {}

		static void from_json(const json& j, SpriteRenderer& sr) {
			j.at("spriteRef").get_to(sr.spriteRef);
			j.at("texture").get_to(sr.texName);
			Core::Point3D::from_json(j.at("scale"), sr.scale);
		}
	};
}}