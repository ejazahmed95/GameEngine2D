#pragma once

#include "Core.h"
#include "CoreModule/CoreSystem.h"
#include "Input/StandardInputReader.h"
#include "Systems.h"

namespace Raven {
	class RAVEN_API Application {
	public:
		Application();
		virtual ~Application();
		virtual void Run();
		virtual void RunWinApp();
		virtual void GameStart();
		virtual void Update(float delta);
		virtual void GameEnd();
		StandardInputReader standardInputReader() const;
		void startGame();
		static Application* Instance();
	private:
		void updateSystems() const;
		StandardInputReader input_reader_;


		bool _gameStarted = false;
		bool _gameEnded = false;
		static Application* _instance;

		// Gameplay Systems
	public:
		Core::CoreSystem* RavenCore() const { return _coreSystem; }
		// Physics::PhysicsSystem* Physics() const { return _physicsSystem; }
	private:
		// Physics::PhysicsSystem* _physicsSystem;
		Core::CoreSystem* _coreSystem;
	};

	// To be defined in Client
	Application* CreateApplication();
}
