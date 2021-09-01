#pragma once
#include "../Core.h"
#include "Point2D.h"

namespace Raven {
	class RAVEN_API GameObject
	{
	public:
		GameObject();
		~GameObject() {
			delete name;
		};

		virtual void Update(float delta);
		
		// Getters
		char* GetName() { return name; }
		Point2D GetPosition() { return position; }

		// Setters
		void SetName(char* name) { this->name = name; }
		void SetPosition(int x, int y) {
			position = Point2D(x, y);
		};
	private:
		char* name;
		Point2D position;
	};
}
