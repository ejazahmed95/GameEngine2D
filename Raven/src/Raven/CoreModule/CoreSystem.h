#pragma once

#include <vector>

#include "GameObject.h"
#include "IGameObjectSystem.h"
#include "../Core.h"

namespace Raven {
namespace Core {

	class RAVEN_API CoreSystem: public IGameObjectSystem {
	private:
		std::vector<GameObject*> _allGameObjects;
	public:
		void Update(float delta) override;
		void Register(IComponent* component) override;
	};

}new 
}
