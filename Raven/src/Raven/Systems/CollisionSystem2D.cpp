#include "CollisionSystem2D.h"
#include "../CoreModule/Entity.h"
#include "../Components/Transform.h"
#include "../Components/PhysicsComponent.h"
#include "RavenStd/Logger.h"
#include "RavenStd/LinearAlgebra/Matrix.h"

namespace Raven { namespace System {

	CollisionSystem2D::CollisionSystem2D() {
		using namespace Components;
		m_Mask.Add(Transform::Id());
		m_Mask.Add(Collider2D::Id());
		m_Mask.Add(PhysicsComponent::Id());
	}

	void CollisionSystem2D::Update(float dt) {
		for (int i = 0; i < m_RegisteredEntities.size(); i++) {
			const auto element1 = m_RegisteredEntities[i];
			const auto collider1 = element1->GetComponent<Components::Collider2D>();
			for (int j = i+1; j < m_RegisteredEntities.size(); j++) {
				const auto element2 = m_RegisteredEntities[j];
				const auto collider2 = element2->GetComponent<Components::Collider2D>();

				bool colliding = (collider1->continuous || collider2->continuous)
					                 ? checkCollisionContinuous(element1, element2, collider1, collider2)
					                 : checkCollision(element1, element2, collider1, collider2);

				if(colliding) {
					collider1->OnCollisionEnterCb(element2);
					collider2->OnCollisionEnterCb(element1);
				}
			}
		}
	}

	bool CollisionSystem2D::checkCollision(Core::Entity* element1, Core::Entity* element2, Components::Collider2D* collider1, Components::Collider2D* collider2) {

		const auto transform1 = element1->GetComponent<Components::Transform>();
		auto transform2 = element2->GetComponent<Components::Transform>();

		// Matrix from A to B
		auto matARot = RavenStd::Matrix::CreateRotationZ(transform1->rotation.Z());
		auto matATrans = RavenStd::Matrix::CreateTranslation(transform1->position.X(), transform1->position.Y(), transform1->position.Z());

		auto matA2World = matATrans * matARot;
		// auto matWorld2A = RavenStd::Matrix::GetInverseWellBehaved(matARot, matATrans);

		auto matBRot = RavenStd::Matrix::CreateRotationZ(transform2->rotation.Z());
		auto matBTrans = RavenStd::Matrix::CreateTranslation(transform2->position.X(), transform2->position.Y(), transform2->position.Z());

		auto matB2World = matBTrans * matBRot;
		auto transVec4 = transform2->position.ToVec4();

		auto matWorld2B = RavenStd::Matrix::GetInverseWellBehaved(matBRot, transVec4);

		auto matA2B = matWorld2B * matA2World;

		// A in B's X Axis
		auto ACenterInB = matA2B * collider1->bounds.center.ToVec4(1);
		auto AExtentXInB = matA2B * RavenStd::Vec4{ collider1->bounds.extents.X(), 0, 0, 0};
		auto AExtentYInB = matA2B * RavenStd::Vec4{ 0, collider1->bounds.extents.Y(), 0, 0 };

		auto AProjXInB = fabs(AExtentXInB.X()) + fabs(AExtentYInB.X());
		auto AProjYInB = fabs(AExtentXInB.Y()) + fabs(AExtentYInB.Y());

		// auto ALeftEdgeInB = ACenterInB.X() - AProjXInB;
		// auto ARightEdgeInB = ACenterInB.X() + AProjXInB;

		{
			// RavenStd::Log::I("matARot\n" + matARot.String());
			// RavenStd::Log::I("matATrans\n" + matATrans.String());
			// RavenStd::Log::I("matA2World\n" + matA2World.String());
			//
			// RavenStd::Log::I("matBRot\n" + matBRot.String());
			// RavenStd::Log::I("matBTrans\n" + matBTrans.String());
			// RavenStd::Log::I("matWorld2B\n" + matWorld2B.String());
			//
			// RavenStd::Log::I("ACenterInB\n" + ACenterInB.toString());
			// RavenStd::Log::I("AExtentXInB\n" + AExtentXInB.toString());
			// RavenStd::Log::I("AExtentYInB\n" + AExtentYInB.toString());
		}

		if(fabs(ACenterInB.X() - collider2->bounds.center.X()) > fabs(collider2->bounds.extents.X()) + fabs(AProjXInB)) {
			// Separation along B's vertical axis
			// RavenStd::Log::I("No Separa")
			return false;
		}

		if (fabs(ACenterInB.Y() - collider2->bounds.center.Y()) > fabs(collider2->bounds.extents.Y()) + fabs(AProjYInB)) {
			// Separation along B's Horizontal Axis
			return false;
		}

		RavenStd::Log::I("Distance between 2 objects is:: X = " + std::to_string(ACenterInB.X() - collider2->bounds.center.X()) +
			"|| Y = " + std::to_string(ACenterInB.Y() - collider2->bounds.center.Y()));

		return true;
	}

	// "Swept" Separation Axis Theorem
	bool CollisionSystem2D::checkCollisionContinuous(Core::Entity* entityA, Core::Entity* entityB, Components::Collider2D* colliderA, Components::Collider2D* colliderB) {
		auto physicsA = entityA->GetComponent<Components::PhysicsComponent>();
		auto physicsB = entityB->GetComponent<Components::PhysicsComponent>();
		// Coordinate System B - X Axis
		auto VelARelB = physicsA->vel - physicsB->vel;
		// auto DistARelB = VelARelB * 
		// Coordinate System B - Y Axis

		return false;
	}

}
}
