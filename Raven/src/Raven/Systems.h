#include "Systems/RenderingSystem.h"

namespace Raven {
	namespace System {
		class InputSystem;
	}

	class ECSManager;
	ECSManager* GetECS();
	System::RenderingSystem* GetRenderer();
	System::InputSystem* GetInputSystem();

	void QuitGame();
}
