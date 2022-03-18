#include "Application.h"

#include <fstream>

#include "RavenStd/Logger.h"
#include "Editor/Editor.h"

namespace Raven {
	Application* Application::_instance = nullptr;

	Application::Application() {
		// _physicsSystem = new Physics::PhysicsSystem();
		_instance = this;
		using namespace System;
		m_Timing = RavenStd::StrongPtr<Timing>(new Timing());
		m_EcsManager = RavenStd::StrongPtr<ECSManager>(new ECSManager());
		m_InputSystem = RavenStd::StrongPtr<System::InputSystem>(new System::InputSystem());
		m_PhysicsSystem = RavenStd::StrongPtr<PhysicsSystem>(new PhysicsSystem());
		m_RenderingSystem = RavenStd::StrongPtr<RenderingSystem>(new RenderingSystem());
	}

	Application::~Application() {
		// delete m_RenderingSystem;
		// delete m_PhysicsSystem;
		// delete m_InputSystem;
		// delete m_EcsManager;
		// delete m_Timing;
	};

	void Application::GameStart() {
		Editor::LoadGameObjectsFromFile("assets/data/scene.json");
	}
	
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

	void Application::App_InitialiseSystems() {
		// TODO: Add Systems to list; Init and Destroy in order
		RavenStd::Log::I("Initializing Systems...");
		m_PhysicsSystem->Initialize();
		m_RenderingSystem->Initialize();
		m_InputSystem->Initialize();
	}

	void Application::App_UpdateSystems(float delta) {
		m_InputSystem->Update(delta);
		m_PhysicsSystem->Update(delta);
		m_RenderingSystem->Update(delta);
	}

	void Application::App_DestroySystems() {
		RavenStd::Log::I("Destroying Systems...");
		m_RenderingSystem->Destroy();
		m_PhysicsSystem->Destroy();
		m_InputSystem->Destroy();
	}

	// Systems.h Implementation
	RavenStd::WeakPtr<ECSManager> GetECS() {
		return Application::Instance()->ECS();
	}

	RavenStd::WeakPtr<System::RenderingSystem> GetRenderer() {
		return Application::Instance()->Renderer();
	}

	RavenStd::WeakPtr<System::InputSystem> GetInputSystem() {
		return Application::Instance()->InputSystem();
	}

	void QuitGame() {
		Application::Instance()->Quit();
	}

}

