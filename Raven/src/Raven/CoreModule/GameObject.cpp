#include "GameObject.h"

namespace Raven {
	GameObject::GameObject()
	{
		name_ = new char[12]{ "Game Object" };
	}

	GameObject::~GameObject()
	{
		delete[] name_;
	}

	void GameObject::onCollisionEnter(GameObject& obj) {
		
	}

	void GameObject::setPosition(int x, int y)
	{
		position_ = Point2D(x, y);
	}

	void GameObject::setVelocity(int x, int y)
	{
		velocity_ = Point2D(x, y);
	}

	void GameObject::update(float delta) {
		position_ = position_ + velocity_;
	}

}
