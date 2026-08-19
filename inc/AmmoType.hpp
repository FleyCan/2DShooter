#pragma once

#include <ostream>

struct AmmoType {
	double bullet_diameter;
	double case_length;

	AmmoType(
		  double bullet_diameter
		, double case_length
	)
		: bullet_diameter{bullet_diameter}
		, case_length{case_length}
	{}

	friend
	bool operator==(
		  AmmoType const& lhs
		, AmmoType const& rhs
	) {
		if(lhs.bullet_diameter == rhs.bullet_diameter) {
			if(lhs.case_length == lhs.bullet_diameter) {
				return true;
			}
		}
		return false;
	}

	friend
	std::ostream& operator<<(
		  std::ostream& os
		, AmmoType const& ammotype
	) {
		os << ammotype.bullet_diameter
		   << " x "
		   << ammotype.case_length;
		return os;
	}
};
