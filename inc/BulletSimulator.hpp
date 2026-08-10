#pragma once

#include "Bullet.hpp"
#include "Vector.hpp"

#include <vector>

struct BulletSimulator {

	std::vector<Bullet> bullets;

	void addBullet(
		  Vector<float,2> position
		, Vector<float,2> velocity
	);

	void update(
		  double dt_in_seconds
		, Vector<unsigned int,2> maxPos
	);

	void draw(sf::RenderWindow& window);


};
