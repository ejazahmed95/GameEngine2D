#pragma once
#include <string>
#include "../Systems.h"

namespace Raven { namespace Editor {
	void AddGameplayComponentsToEntity(Core::Entity* entity, json componentObj);
	void LoadGameObjectsFromFile(std::string fileName);
	void LoadAssetsFromFile(std::string fileNames);
	void LoadConfig();
}}
