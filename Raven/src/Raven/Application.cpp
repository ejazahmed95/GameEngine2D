#include "Application.h"

namespace Raven {
	Application* Application::_instance = nullptr;

	Application::Application() {
		// _physicsSystem = new Physics::PhysicsSystem();
		_instance = this;
		m_EcsManager = new ECSManager();
		m_RenderingSystem = new System::RenderingSystem();
		m_InputSystem = new System::InputSystem();
	}

	Application::~Application() {
		delete m_InputSystem;
		delete m_RenderingSystem;
		delete m_EcsManager;
	};

	void Application::GameStart() {}
	void Application::Update(float delta) {}
	void Application::GameEnd() {}

	// StandardInputReader Application::standardInputReader() const
	// {
	// 	return input_reader_;
	// }

	void Application::App_StartGame() {
		if (m_GameStarted) return;

		App_InitialiseSystems();
		GameStart();

		// TODO: Calculate and add the delta time for each of these
		while(!m_GameEnded) {
			App_UpdateSystems();
			Update(1);
		}

		GameEnd();
		App_DestroySystems();
	}

	void Application::Quit() {
		m_GameEnded = true;
	}

	Application* Application::Instance() {
		return Application::_instance;
	}

	void Application::App_InitialiseSystems() const {
		SLib::Log::I("Initializing Systems...");
		m_RenderingSystem->Initialize();
		m_InputSystem->Initialize();
	}

	void Application::App_UpdateSystems() const {
		m_RenderingSystem->Update(1.0f);
		m_InputSystem->Update(1.0f);
	}

	void Application::App_DestroySystems() const {
		SLib::Log::I("Destroying Systems...");
		m_RenderingSystem->Destroy();
		m_InputSystem->Destroy();
	}


	ECSManager* GetECS() {
		return Application::Instance()->ECS();
	}

	System::RenderingSystem* GetRenderer() {
		return Application::Instance()->Renderer();
	}

	System::InputSystem* GetInputSystem() {
		return Application::Instance()->InputSystem();
	}

	void QuitGame() {
		Application::Instance()->Quit();
	}

}

