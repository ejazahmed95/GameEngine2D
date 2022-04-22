#include "InputSystem.h"
#include "../Components/InputComponent.h"
#include "../Systems.h"
#include "../CoreModule/Entity.h"
#include "RavenStd/Logger.h"

namespace Raven { namespace System {

	InputSystem::InputSystem() {
		using namespace Components;
		m_Mask.Add(InputComponent::Id());
	}

	void InputSystem::Initialize() {
		BaseSystem::Initialize();
		// std::function<void(unsigned i_VKeyID, bool i_bDown)> OnInputChange;
		//auto callback = [this] { OnInChange(); };
		GLib::SetKeyStateChangeCallback(OnInputChange);
	}

	void InputSystem::Update(float dt) {
		
	}

	void InputSystem::Destroy() {
		BaseSystem::Destroy();
	}

	void InputSystem::OnInChange(unsigned i_VKeyID, bool bWentDown) {
		for (auto & entity : m_RegisteredEntities) {
			auto inputComp = entity->GetComponent<Components::InputComponent>();

			inputComp->OnInputChange(i_VKeyID, bWentDown);
		}
	}

	void OnInputChange(unsigned int i_VKeyID, bool bWentDown)
	{
		std::string s = (bWentDown) ? "PRESSED" : "RELEASED";
		RavenStd::Log::T("Input ::" + s + " KeyID=" + std::to_string(i_VKeyID));
		if(bWentDown && i_VKeyID == 0x0051) {
			QuitGame();
			return;
		}

		GetInputSystem().AcquireOwnership()->OnInChange(i_VKeyID, bWentDown);

	}
}
}
