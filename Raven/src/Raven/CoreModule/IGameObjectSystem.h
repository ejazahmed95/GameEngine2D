#pragma once

/// <summary>
/// It is the base interface for systems that act on game objects
/// </summary>
class RAVEN_API IGameObjectSystem {
public:
	virtual ~IGameObjectSystem() = default;
	virtual void Update(float delta) = 0;
	virtual void Register(Raven::IComponent* component) = 0;
};