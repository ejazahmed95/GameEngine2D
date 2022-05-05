#include "Transform.h"

namespace Raven { namespace Components {

	void Transform::Translate(Core::Point3D distance) {
		position += distance;
	}

	void Transform::Rotate(Core::Point3D rot) {
		rotation += rot;
	}

	RavenStd::Matrix Transform::Object2WorldMatrix() const {
		// Matrix from A to B
		auto matARot = RavenStd::Matrix::CreateRotationZ(rotation.Z());
		auto matATrans = RavenStd::Matrix::CreateTranslation(position.X(), position.Y(), position.Z());

		return matATrans * matARot;
	}

	RavenStd::Matrix Transform::World2ObjectMatrix() const {
		auto matARot = RavenStd::Matrix::CreateRotationZ(rotation.Z());
		auto transVec4 = position.ToVec4();

		return RavenStd::Matrix::GetInverseWellBehaved(matARot, transVec4);
	}
}}
