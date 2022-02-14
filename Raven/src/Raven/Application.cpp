#include "Application.h"

namespace Raven {
	Application* Application::_instance = nullptr;

	Application::Application() {
		// _physicsSystem = new Physics::PhysicsSystem();
		_instance = this;
		m_EcsManager = new ECSManager();
		m_RenderingSystem = new System::RenderingSystem();
	}

	Application::~Application() = default;

	void Application::GameStart() {}
	void Application::Update(float delta) {}
	void Application::GameEnd() {}

	// StandardInputReader Application::standardInputReader() const
	// {
	// 	return input_reader_;
	// }

	void Application::App_StartGame() {
		if (_gameStarted) return;

		App_InitialiseSystems();
		GameStart();

		// TODO: Calculate and add the delta time for each of these
		while(!_gameEnded) {
			App_UpdateSystems();
			Update(1);
		}

		GameEnd();
		App_DestroySystems();
	}

	Application* Application::Instance() {
		return Application::_instance;
	}

	void Application::App_InitialiseSystems() const {
		SLib::Log::I("Initializing Systems...");
		m_RenderingSystem->Initialize();
	}

	void Application::App_UpdateSystems() const {
		m_RenderingSystem->Update(1.0f);
	}

	void Application::App_DestroySystems() const {
		SLib::Log::I("Destroying Systems...");
		m_RenderingSystem->Destroy();
	}


	ECSManager* GetECS() {
		return Application::Instance()->ECS();
	}

	System::RenderingSystem* GetRenderer() {
		return Application::Instance()->Renderer();
	}

}

