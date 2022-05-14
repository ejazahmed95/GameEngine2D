#pragma once
#include "Raven/Systems/BaseSystem.h"

namespace Systems {
	class HealthSystem : public Raven::System::BaseSystem {
	public:
		HealthSystem();
		void Update(float dt) override;
		int GetEnemyDeadCount() const { return m_EnemyDeadCount; }
		int GetPlayerDeadCount() const { return m_PlayerDeadCount; }
	private:
		int m_EnemyDeadCount, m_PlayerDeadCount;
	};
}
