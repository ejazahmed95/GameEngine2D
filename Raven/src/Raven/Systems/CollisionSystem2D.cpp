#include "CollisionSystem2D.h"
#include "../CoreModule/Entity.h"
#include "../Components/Transform.h"
#include "../Components/PhysicsComponent.h"
#include "RavenStd/Logger.h"
#include "RavenStd/Utils.h"
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
			if (element1->Destroyed()) continue;
			const auto collider1 = element1->GetComponent<Components::Collider2D>();
			for (int j = i+1; j < m_RegisteredEntities.size(); j++) {
				const auto element2 = m_RegisteredEntities[j];
				if (element1->Destroyed() || element2->Destroyed()) continue;
				if (element1->GetTag() == element2->GetTag()) continue;
				const auto collider2 = element2->GetComponent<Components::Collider2D>();

				bool colliding = (collider1->continuous || collider2->continuous)
					                 ? checkCollisionContinuous(element1, element2, collider1, collider2, dt)
					                 : checkCollision(element1, element2, collider1, collider2);

				if(colliding) {
					collider1->OnCollisionEnterCb(element2);
					collider2->OnCollisionEnterCb(element1);
				}
			}
		}
	}

	bool CollisionSystem2D::checkCollision(Core::Entity* elementA, Core::Entity* elementB, Components::Collider2D* colliderA, Components::Collider2D* colliderB) const {

		const auto transformA = elementA->GetComponent<Components::Transform>();
		auto transformB = elementB->GetComponent<Components::Transform>();

		// Matrix from A to B
		auto matARot = RavenStd::Matrix::CreateRotationZ(transformA->rotation.Z());
		auto matATrans = RavenStd::Matrix::CreateTranslation(transformA->position.X(), transformA->position.Y(), transformA->position.Z());

		auto matA2World = matATrans * matARot;
		// auto matWorld2A = RavenStd::Matrix::GetInverseWellBehaved(matARot, matATrans);

		auto matBRot = RavenStd::Matrix::CreateRotationZ(transformB->rotation.Z());
		auto matBTrans = RavenStd::Matrix::CreateTranslation(transformB->position.X(), transformB->position.Y(), transformB->position.Z());

		auto matB2World = matBTrans * matBRot;
		auto transVec4 = transformB->position.ToVec4();

		auto matWorld2B = RavenStd::Matrix::GetInverseWellBehaved(matBRot, transVec4);

		auto matA2B = matWorld2B * matA2World;

		// A in B's X Axis
		auto ACenterInB = matA2B * colliderA->bounds.center.ToVec4(1);
		auto AExtentXInB = matA2B * RavenStd::Vec4{ colliderA->bounds.extents.X(), 0, 0, 0};
		auto AExtentYInB = matA2B * RavenStd::Vec4{ 0, colliderA->bounds.extents.Y(), 0, 0 };

		auto AProjXInB = fabs(AExtentXInB.X()) + fabs(AExtentYInB.X());
		auto AProjYInB = fabs(AExtentXInB.Y()) + fabs(AExtentYInB.Y());


		if(fabs(ACenterInB.X() - colliderB->bounds.center.X()) > fabs(colliderB->bounds.extents.X()) + fabs(AProjXInB)) {
			// Separation along B's vertical axis
			return false;
		}

		if (fabs(ACenterInB.Y() - colliderB->bounds.center.Y()) > fabs(colliderB->bounds.extents.Y()) + fabs(AProjYInB)) {
			// Separation along B's Horizontal Axis
			return false;
		}


		// B in A's X Axis
		auto tVec = transformA->position.ToVec4();
		auto matWorld2A = RavenStd::Matrix::GetInverseWellBehaved(matARot, tVec);
		auto matB2A = matWorld2A * matB2World;

		auto BCenterInA = matB2A * colliderB->bounds.center.ToVec4(1);
		auto BExtentXInA = matB2A * RavenStd::Vec4{ colliderA->bounds.extents.X(), 0, 0, 0 };
		auto BExtentYInA = matB2A * RavenStd::Vec4{ 0, colliderA->bounds.extents.Y(), 0, 0 };

		auto BProjXInA = fabs(BExtentXInA.X()) + fabs(BExtentYInA.X());
		auto BProjYInA = fabs(BExtentXInA.Y()) + fabs(BExtentYInA.Y());

		if (fabs(BCenterInA.X() - colliderA->bounds.center.X()) > fabs(colliderA->bounds.extents.X()) + fabs(BProjXInA)) {
			// Separation along B's vertical axis
			return false;
		}

		if (fabs(BCenterInA.Y() - colliderA->bounds.center.Y()) > fabs(colliderA->bounds.extents.Y()) + fabs(BProjYInA)) {
			// Separation along B's Horizontal Axis
			return false;
		}

		//RavenStd::Log::I("Distance between 2 objects is:: X = " + std::to_string(ACenterInB.X() - colliderB->bounds.center.X()) +
			//"|| Y = " + std::to_string(ACenterInB.Y() - colliderB->bounds.center.Y()));

		return true;
	}

	// "Swept" Separation Axis Theorem
	bool CollisionSystem2D::checkCollisionContinuous(Core::Entity* entityA, Core::Entity* entityB, Components::Collider2D* colliderA, Components::Collider2D* colliderB, float dt) {
		auto physicsA = entityA->GetComponent<Components::PhysicsComponent>();
		auto physicsB = entityB->GetComponent<Components::PhysicsComponent>();

		// Ranging time from 0(t=0) to 1(t=dt) for easier calculations
		float tClose = 0;
		float tOpen = 1;

		const auto transformA = entityA->GetComponent<Components::Transform>();
		const auto transformB = entityB->GetComponent<Components::Transform>();

		bool separated = false;

		/*
		 * B's Coordinate System
		 * B's X-Axis
		 */ 
		const auto& matA2B = getMatA2B(transformA, transformB);
		auto ACenterInB = matA2B * colliderA->bounds.center.ToVec4(1);

		auto AExtentXInB = matA2B * RavenStd::Vec4{ colliderA->bounds.extents.X(), 0, 0, 0 };
		auto AExtentYInB = matA2B * RavenStd::Vec4{ 0, colliderA->bounds.extents.Y(), 0, 0 };
		auto AProjInB = Core::Point3D{ fabs(AExtentXInB.X()) + fabs(AExtentYInB.X()), fabs(AExtentXInB.Y()) + fabs(AExtentYInB.Y()), 0 };
		Core::Point3D expandedExtentsB = colliderB->bounds.extents + AProjInB;

		auto VelARelB = physicsA->vel - physicsB->vel;
		auto VelADist = VelARelB * dt;
		auto VelADistInBx = RavenStd::Vec4::Dot(transformB->World2ObjectMatrix().Column(0).Normalize(), VelADist.ToVec4());

		auto bLeft = colliderB->bounds.center.X() - expandedExtentsB.X();
		auto bRight = colliderB->bounds.center.X() + expandedExtentsB.X();

		updateTimes(ACenterInB.X(), bLeft, bRight, VelADistInBx, tOpen, tClose, separated);

		//RavenStd::Log::D("CS = B | X-Axis || Point = " + std::to_string(ACenterInB.X()) + "| Edge_L = " + std::to_string(bLeft) +
			//"| Edge_R = " + std::to_string(bRight) + "| Distance = " + std::to_string(VelADistInBx));

		if (separated) return false;


		/*
		 * B's Coordinate System
		 * B's Y-Axis
		 */
		auto VelADistInBy = RavenStd::Vec4::Dot(transformB->World2ObjectMatrix().Column(1).Normalize(), VelADist.ToVec4());

		auto bBottom = colliderB->bounds.center.Y() - expandedExtentsB.Y();
		auto bTop = colliderB->bounds.center.Y() + expandedExtentsB.Y();
		updateTimes(ACenterInB.Y(), bBottom, bTop, VelADistInBy, tOpen, tClose, separated);

		if (separated) return false;


		/*
		 * A's Coordinate System
		 * A's X-Axis
		 */

		const auto& matB2A = getMatA2B(transformB, transformA);
		auto BCenterInA = matB2A * colliderA->bounds.center.ToVec4(1);

		auto BExtentXInA = matB2A * RavenStd::Vec4{ colliderB->bounds.extents.X(), 0, 0, 0 };
		auto BExtentYInA = matB2A * RavenStd::Vec4{ 0, colliderB->bounds.extents.Y(), 0, 0 };
		auto BProjInA = Core::Point3D{ fabs(BExtentXInA.X()) + fabs(BExtentYInA.X()), fabs(BExtentXInA.Y()) + fabs(BExtentYInA.Y()), 0 };
		Core::Point3D expandedExtentsA = colliderA->bounds.extents + BProjInA;

		auto VelBRelA = physicsB->vel - physicsA->vel;
		auto VelBDist = VelBRelA * dt;
		auto VelBDistInAx = RavenStd::Vec4::Dot(transformA->World2ObjectMatrix().Column(0).Normalize(), VelBDist.ToVec4());

		bLeft = colliderA->bounds.center.X() - expandedExtentsA.X();
		bRight = colliderA->bounds.center.X() + expandedExtentsA.X();

		updateTimes(BCenterInA.X(), bLeft, bRight, VelBDistInAx, tOpen, tClose, separated);

		//RavenStd::Log::D("CS = B | X-Axis || Point = " + std::to_string(ACenterInB.X()) + "| Edge_L = " + std::to_string(bLeft) +
			//"| Edge_R = " + std::to_string(bRight) + "| Distance = " + std::to_string(VelADistInBx));

		if (separated) return false;


		/*
		 * A's Coordinate System
		 * A's Y-Axis
		 */
		auto VelBDistInAy = RavenStd::Vec4::Dot(transformA->World2ObjectMatrix().Column(1).Normalize(), VelBDist.ToVec4());

		bBottom = colliderA->bounds.center.Y() - expandedExtentsA.Y();
		bTop = colliderA->bounds.center.Y() + expandedExtentsA.Y();
		updateTimes(BCenterInA.X(), bBottom, bTop, VelBDistInAy, tOpen, tClose, separated);

		if (separated) return false;

		// Time of Collision
		// Todo: Use time of collision to update the velocities
		auto tCol = tClose * dt;

		// Coordinate System B - Y Axis
		return tOpen > tClose;
	}

	void CollisionSystem2D::updateTimes(float center, float bLeft, float bRight, float distance, float& tOpen, float& tClose, bool& separated) {
		if (fabs(distance) <= 0.000001f) {
			if (center < bLeft || center > bRight) {
				separated = true;
				return;
			}
		}

		float currentTClose = (bLeft - center) / distance;
		float currentTOpen = (bRight - center) / distance;

		if(currentTOpen < currentTClose) {
			RavenStd::Swap(currentTClose, currentTOpen);
		}

		if(currentTOpen < 0 || currentTClose > 1) {
			separated = true;
			return;
		}

		tClose = RavenStd::Max(tClose, currentTClose);
		tOpen = RavenStd::Min(tOpen, currentTOpen);
	}

	RavenStd::Matrix CollisionSystem2D::getMatA2B(Components::Transform* transformA, Components::Transform* transformB) {
		auto matWorld2B = transformB->World2ObjectMatrix();
		auto matA2World = transformA->Object2WorldMatrix();

		
		return matWorld2B * matA2World;
	}

}
}
