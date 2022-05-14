#pragma once
#include <functional>

#include "SpriteRenderer.h"
#include "TComponent.h"
#include "../CoreModule/Point3D.h"
#include "../CoreModule/Entity.h"
#include "GLib.h"

namespace Raven {namespace Components {

	//struct CollisionLayer {
		//static Types::t_uid s_id;
		//static Types::t_uid Get();
	//};

	struct RAVEN_API AABB {
		Core::Point3D center;
		Core::Point3D extents;

		AABB() : center(0), extents(0) {}
		AABB(Core::Point3D center, Core::Point3D extents): center(center), extents(extents) {}
	};

	struct RAVEN_API Collider2D : public TComponent<Collider2D> {
		AABB bounds;
		bool continuous = false;
		GLib::Sprite* collisionBox;
		std::function<void(Core::Entity*)> OnCollisionEnterCb = nullptr;
	public:
		Collider2D() {
			OnCollisionEnterCb = [](Core::Entity*)->void*{return nullptr; };
			collisionBox = nullptr;
		}

		void SetCallback(const std::function<void(Core::Entity*)>& cb) {
			OnCollisionEnterCb = cb;
		}

		static void from_json(const json& j, Components::Collider2D& c) {
			auto bounds = j.at("bounds");
			if (j.contains("continuous")) j.at("continuous").get_to(c.continuous);
			Core::Point3D::from_json(bounds.at("center"), c.bounds.center);
			Core::Point3D::from_json(bounds.at("extents"), c.bounds.extents);
		}
	};

}}
