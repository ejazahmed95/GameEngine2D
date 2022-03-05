#include "Application.h"
#include "RavenStd/Logger.h"

namespace Raven {
	Application* Application::_instance = nullptr;

	Application::Application() {
		// _physicsSystem = new Physics::PhysicsSystem();
		_instance = this;
		m_Timing = new Timing();
		m_EcsManager = new ECSManager();
		m_InputSystem = new System::InputSystem();
		m_PhysicsSystem = new System::PhysicsSystem();
		m_RenderingSystem = new System::RenderingSystem();
	}

	Application::~Application() {
		delete m_RenderingSystem;
		delete m_PhysicsSystem;
		delete m_InputSystem;
		delete m_EcsManager;
		delete m_Timing;
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
			float delta = m_Timing->GetFrameTime();
			// SLib::Log::I("Last Frame Time = " + std::to_string(static_cast<int>(delta*1000)) + "ms");
			App_UpdateSystems(delta);
			Update(delta);
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
		// TODO: Add Systems to list; Init and Destroy in order
		RavenStd::Log::I("Initializing Systems...");
		m_PhysicsSystem->Initialize();
		m_RenderingSystem->Initialize();
		m_InputSystem->Initialize();
	}

	void Application::App_UpdateSystems(float delta) const {
		m_InputSystem->Update(delta);
		m_PhysicsSystem->Update(delta);
		m_RenderingSystem->Update(delta);
	}

	void Application::App_DestroySystems() const {
		RavenStd::Log::I("Destroying Systems...");
		m_RenderingSystem->Destroy();
		m_PhysicsSystem->Destroy();
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

