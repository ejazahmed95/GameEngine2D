#include "Monster.h"

std::ostream& operator<<(std::ostream& lhs, const Monster& m) {
	lhs << m.name_ << "=> Pos = "<< m.position().toString() << ", Vel = " << m.velocity().toString();
	return lhs;
}