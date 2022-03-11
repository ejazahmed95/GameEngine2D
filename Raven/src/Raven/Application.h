#pragma once

#include "Core.h"
#include "ECSManager.h"
#include "Timing.h"
#include "RavenStd/memory/StrongPointer.h"
#include "RavenStd/memory/WeakPointer.h"
#include "Systems/InputSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/RenderingSystem.h"

namespace Raven {
	class RAVEN_API Application {
	public:
		Application();
		virtual ~Application();
		virtual void GameStart();
		virtual void Update(float delta);
		virtual void GameEnd();
		//StandardInputReader standardInputReader() const;
		void App_StartGame();
		void Quit();
		static Application* Instance();
	private:
		void App_InitialiseSystems();
		void App_UpdateSystems(float delta);
		void App_DestroySystems();
		//StandardInputReader input_reader_;

		bool m_GameStarted = false;
		bool m_GameEnded = false;
		static Application* _instance;

		// Gameplay Systems
	public:
		RavenStd::WeakPtr<ECSManager> ECS() const { return m_EcsManager;  }
		RavenStd::WeakPtr<System::RenderingSystem> Renderer() const { return m_RenderingSystem; }
		RavenStd::WeakPtr<System::InputSystem> InputSystem() const { return m_InputSystem; }
		RavenStd::WeakPtr<System::PhysicsSystem> Physics() const { return m_PhysicsSystem; }
	private:
		RavenStd::StrongPtr<Timing> m_Timing;
		RavenStd::StrongPtr<ECSManager> m_EcsManager;
		RavenStd::StrongPtr<System::RenderingSystem> m_RenderingSystem;
		RavenStd::StrongPtr<System::InputSystem> m_InputSystem;
		RavenStd::StrongPtr<System::PhysicsSystem> m_PhysicsSystem;
	};

	// To be defined in Client
	Application* CreateApplication();
}
