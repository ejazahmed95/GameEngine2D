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

	bool CollisionSystem2D::checkCollision(Core::Entity* element1, Core::Entity* element2, Components::Collider2D* collider1, Components::Collider2D* collider2) const {

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
		Core::Point3D expandedExtents = colliderB->bounds.extents + AProjInB;

		auto VelARelB = physicsA->vel - physicsB->vel;
		auto VelADist = VelARelB * dt;
		auto VelADistInB = RavenStd::Vec4::Dot(transformB->World2ObjectMatrix().Column(0).Normalize(), VelADist.ToVec4());

		auto bLeft = colliderB->bounds.center.X() - expandedExtents.X();
		auto bRight = colliderB->bounds.center.X() + expandedExtents.X();

		updateTimes(ACenterInB.X(), bLeft, bRight, VelADistInB, tOpen, tClose, separated);

		RavenStd::Log::D("CS = B | X-Axis || Point = " + std::to_string(ACenterInB.X()) + "| Edge_L = " + std::to_string(bLeft) +
			"| Edge_R = " + std::to_string(bRight) + "| Distance = " + std::to_string(VelADistInB));

		if (separated) return false;

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
