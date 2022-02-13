#pragma once

#include "Core.h"
#include "ECSManager.h"
#include "CoreModule/CoreSystem.h"
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
		static Application* Instance();
	private:
		void App_InitialiseSystems() const;
		void App_UpdateSystems() const;
		void App_DestroySystems() const;
		//StandardInputReader input_reader_;

		bool _gameStarted = false;
		bool _gameEnded = false;
		static Application* _instance;

		// Gameplay Systems
	public:
		ECSManager* ECS() const { return m_EcsManager;  }
		Core::CoreSystem* RavenCore() const { return m_CoreSystem; }
		System::RenderingSystem* Renderer() const { return m_RenderingSystem; }
		// Physics::PhysicsSystem* Physics() const { return _physicsSystem; }
	private:
		// Physics::PhysicsSystem* _physicsSystem;
		ECSManager* m_EcsManager;
		Core::CoreSystem* m_CoreSystem;
		System::RenderingSystem* m_RenderingSystem{};
	};

	// To be defined in Client
	Application* CreateApplication();
}
