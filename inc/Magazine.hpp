#pragma once

#include <vector>
#include <optional>

#include "AmmoType.hpp"
#include "Ammunition.hpp"

#include <iostream>

struct Magazine : std::vector<Ammunition> {

	AmmoType ammotype;
	int max_size;

	Magazine(AmmoType ammotype, int size)
		: ammotype{ammotype}
		, max_size{size}
	{}

	Magazine(Magazine const& magazine)
		: ammotype{magazine.ammotype}
		, max_size{magazine.max_size}
	{}

	void addAmmo(Ammunition ammo) {
		/*if(    ammo.type == ammotype
			&& size() < max_size
		) */{
			push_back(ammo);
			std::cout << "push_back(" << ammo << ")\n";
			std::cout << size() << '\n';
		}
	}

	std::optional<Ammunition> getAmmo() {
		if(!empty()) {
			return back();
		} else {
			return std::nullopt;
		}
	}

	void removeAmmo() {
		pop_back();
	}

};
