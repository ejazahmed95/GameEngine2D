#pragma once

#include "Core.h"
#include "ECSManager.h"
#include "Systems/InputSystem.h"
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
		void App_InitialiseSystems() const;
		void App_UpdateSystems() const;
		void App_DestroySystems() const;
		//StandardInputReader input_reader_;

		bool m_GameStarted = false;
		bool m_GameEnded = false;
		static Application* _instance;

		// Gameplay Systems
	public:
		ECSManager* ECS() const { return m_EcsManager;  }
		System::RenderingSystem* Renderer() const { return m_RenderingSystem; }
		System::InputSystem* InputSystem() const { return m_InputSystem; }
		// Physics::PhysicsSystem* Physics() const { return _physicsSystem; }
	private:
		// Physics::PhysicsSystem* _physicsSystem;
		ECSManager* m_EcsManager;
		System::RenderingSystem* m_RenderingSystem;
		System::InputSystem* m_InputSystem;
	};

	// To be defined in Client
	Application* CreateApplication();
}
