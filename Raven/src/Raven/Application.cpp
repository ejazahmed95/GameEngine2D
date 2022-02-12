#include "Application.h"

namespace Raven {
	Application* Application::_instance = nullptr;
	Application::Application() {
		_coreSystem = new Core::CoreSystem();
		// _physicsSystem = new Physics::PhysicsSystem();
		_instance = this;
	}

	Application::~Application() = default;

	void Application::Run() {
		while (true);
	}

	void Application::RunWinApp() {
		while (true);
	}

	void Application::GameStart() {}
	void Application::Update(float delta) {}
	void Application::GameEnd() {}

	StandardInputReader Application::standardInputReader() const
	{
		return input_reader_;
	}

	void Application::startGame() {
		if (_gameStarted) return;

		GameStart();

		// TODO: Calculate and add the delta time for each of these
		while(!_gameEnded) {
			updateSystems();
			Update(1);
		}

		GameEnd();
	}

	Application* Application::Instance() {
		return Application::_instance;
	}

	void Application::updateSystems() const {
		_coreSystem->Update(1.0f);
	}

	IGameObjectSystem* RavenCore() {
		return Application::Instance()->RavenCore();
	}

}

