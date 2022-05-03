#pragma once
#include <functional>
#include "TComponent.h"
#include "../CoreModule/Entity.h"
#include "GLib.h"

namespace Raven {namespace Components {

	struct CollisionLayer {
		static Types::t_uid s_id;
		static Types::t_uid Get();
	};

	struct RAVEN_API Collider2D : TComponent<Collider2D> {

		std::function<void(Core::Entity*)> OnCollisionEnterCb = nullptr;

		Collider2D() {
			OnCollisionEnterCb = [](Core::Entity*)->void*{return nullptr; };
		}

		void SetCallback(const std::function<void(Core::Entity*)>& cb) {
			OnCollisionEnterCb = cb;
		}
	};

}}
