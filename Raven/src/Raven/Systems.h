#include "RavenStd/memory/WeakPointer.h"
#include "Systems/RenderingSystem.h"

namespace Raven {
	namespace System {
		class InputSystem;
	}

	class ECSManager;
	RavenStd::WeakPtr<ECSManager> GetECS();
	RavenStd::WeakPtr<System::RenderingSystem> GetRenderer();
	RavenStd::WeakPtr<System::InputSystem> GetInputSystem();

	void QuitGame();
}
