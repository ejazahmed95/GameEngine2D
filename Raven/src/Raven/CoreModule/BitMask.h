#pragma once
#include "Types.h"

namespace Raven {
	class BitMask {
	public:
		void Add(Types::t_uid bitIndex) {
			mask |= (static_cast<Types::t_uid>(1) << bitIndex);
		}

		void Remove(Types::t_uid bitIndex) {
			mask &= ~(static_cast<Types::t_uid>(1) << bitIndex);
		}

		bool At(int bitIndex) {
			return (mask & (static_cast<Types::t_uid>(1) << bitIndex)) != 0;
		}

		bool contains(const BitMask& otherMask) {
			return otherMask.GetValue() == (mask & otherMask.GetValue());
		}

		Types::t_uid GetValue() const { return mask; }
	private:
		Types::t_uid mask = 0;
	};
}

