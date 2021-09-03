#pragma once
#include "../Core.h"
#include "Point2D.h"

namespace Raven {
	class RAVEN_API GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(float delta);
		virtual void onCollisionEnter(GameObject& obj);

		// Getters
		char* name() const { return name_; }
		Point2D position() const { return position_; }
		Point2D velocity() const { return velocity_; }

		// Setters
		void setName(char* name) { name_ = name; }
		void setPosition(int x, int y);
		void setVelocity(int x, int y);
	private:
		char* name_;
		Point2D position_;
		Point2D velocity_;
	};
}
