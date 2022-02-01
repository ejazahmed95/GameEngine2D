#pragma once
#include "../Core.h"

/// <summary>
/// Base interface of all components
/// </summary>
namespace Raven {
	class RAVEN_API IComponent {
	public:
		virtual ~IComponent() = default;
	};
}