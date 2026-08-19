#pragma once

#include "Bullet.hpp"
#include "Vector.hpp"

#include <vector>

struct BulletSimulator {

	std::vector<Bullet> bullets;

	void addBullet(Bullet const& bullet);

	void update(
		  double dt_in_seconds
		, Vector<unsigned int,2> maxPos
	);

	void draw(sf::RenderWindow& window);


};
