#include "Monster.h"
#include <iostream>

std::ostream& operator<<(std::ostream& lhs, const Monster& m) {
	lhs << m.name_ << "=> Pos = " << m.position() << ", Vel = " << m.velocity();
	return lhs;
}