#pragma once

#include "AmmoType.hpp"

#include <ostream>

struct Ammunition {

	AmmoType type;

	int damage;
	int penetration;
	int speed;

	Ammunition(
		  AmmoType type
		, int damage
		, int penetration
		, int speed
	)
		: type{type}
		, damage{damage}
		, penetration{penetration}
		, speed{speed}
	{}

	friend std::ostream& operator<<(
		  std::ostream& os
		, Ammunition const& ammunition
	) {
		os << ammunition.type << '\n'
		   << ammunition.damage << '\n'
		   << ammunition.penetration << '\n'
		   << ammunition.speed << '\n';

		return os;
	}
};
