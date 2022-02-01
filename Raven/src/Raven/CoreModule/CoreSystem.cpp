#include "CoreSystem.h"

namespace Raven { namespace Core {

	void CoreSystem::Update(float delta) {
		for (int i = 0; i < _allGameObjects.size();i++) {
			_allGameObjects[i]->update(delta);
		}
	}

	void CoreSystem::Register(IComponent* component) {
		auto go = dynamic_cast<GameObject*>(component);
		if (go == nullptr) return;
		if(go) _allGameObjects.push_back(go);
	}
	
}}
