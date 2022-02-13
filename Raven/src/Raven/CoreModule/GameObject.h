#pragma once
#include "IComponent.h"
#include "../Core.h"
#include "Point2D.h"

namespace Raven {
	class RAVEN_API GameObject:public IComponent {
	public:
		GameObject();
		~GameObject();

		virtual void update(float delta);
		virtual void onCollisionEnter(GameObject& obj);

		// Getters
		std::string name() const { return name_; }
		Point2D position() const { return position_; }
		Point2D velocity() const { return velocity_; }

		// Setters
		void setName(char* name) { name_ = name; }
		void setPosition(int x, int y);
		void setVelocity(int x, int y);

		// Component methods

	private:
		std::string name_;
		Point2D position_;
		Point2D velocity_;
	};
}
