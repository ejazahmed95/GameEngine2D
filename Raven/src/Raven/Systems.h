#include "CoreModule/IGameObjectSystem.h"
#include "Systems/RenderingSystem.h"

namespace Raven {
	class ECSManager;
	ECSManager* GetECS();
	System::RenderingSystem* GetRenderer();
	IGameObjectSystem* RavenCore();
}
