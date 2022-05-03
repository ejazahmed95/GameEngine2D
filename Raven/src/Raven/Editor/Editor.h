#pragma once
#include <string>
#include "../Systems.h"

namespace Raven { namespace Editor {
	void LoadGameObjectsFromFile(std::string fileName);
	void LoadAssetsFromFile(std::string fileNames);
	void LoadConfig();
}}
