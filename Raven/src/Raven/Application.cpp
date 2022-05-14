#include "Application.h"

#include <fstream>

#include "RavenStd/Logger.h"
#include "Editor/Editor.h"
#include "JobSystem/JobSystem.h"

namespace Raven {
	Application* Application::_instance = nullptr;

	Application::Application() {
		// _physicsSystem = new Physics::PhysicsSystem();
		_instance = this;

		using namespace System;
		auto timing = new Timing();
		m_Timing = RavenStd::StrongPtr<Timing>(timing);
		m_EcsManager = RavenStd::StrongPtr<ECSManager>(new ECSManager());

		m_InputSystem = RavenStd::StrongPtr<System::InputSystem>(new System::InputSystem());
		m_CollisionSystem = RavenStd::StrongPtr<CollisionSystem2D>(new CollisionSystem2D());
		m_PhysicsSystem = RavenStd::StrongPtr<PhysicsSystem>(new PhysicsSystem());
		m_RenderingSystem = RavenStd::StrongPtr<RenderingSystem>(new RenderingSystem());
	}

	void Application::GameStart() {
		Engine::JobSystem::Init();
		m_EcsManager->Initialize();
		Editor::LoadAssetsFromFile("assets/data/assets.json");
		Editor::LoadGameObjectsFromFile("assets/data/scene.json");
	}
	
	void Application::Update(float delta) {
		m_EcsManager->Update(delta);
	}

	void Application::GameEnd() {
		RavenStd::Log::I("Shutting down game");
		Engine::JobSystem::RequestShutdown();
		m_EcsManager->Shutdown();
	}

	void Application::App_StartGame() {
		if (m_GameStarted) return;

		App_InitialiseSystems();
		GameStart(); // Virtual
		
		while(!m_GameEnded) {
			float delta = m_Timing->GetFrameTime(0.01f);
			// RavenStd::Log::I("Last Frame Time = " + std::to_string(delta*1000) + "ms");
			App_UpdateSystems(delta);
			Update(delta);
		}

		GameEnd(); // Virtual
	}

	void Application::Quit() {
		m_GameEnded = true;
	}

	Application* Application::Instance() {
		return Application::_instance;
	}

	void Application::App_InitialiseSystems() {
		

		// TODO: Add Systems to list; Init and Shutdown in order
		RavenStd::Log::I("Initializing Systems...");
		// m_CollisionSystem->Initialize();
		// m_PhysicsSystem->Initialize();
		// m_RenderingSystem->Initialize();
		// m_InputSystem->Initialize();
	}

	void Application::App_UpdateSystems(float delta) {

	}

	void Application::App_DestroySystems() {
		RavenStd::Log::I("Destroying Systems...");
		m_RenderingSystem->Destroy();
		m_PhysicsSystem->Destroy();
		m_CollisionSystem->Destroy();
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

