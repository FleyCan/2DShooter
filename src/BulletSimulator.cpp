#include "BulletSimulator.hpp"

void BulletSimulator::addBullet(
	Vector<float,2> position
	, Vector<float,2> velocity
) {
	bullets.push_back(
		Bullet{
			position
			, velocity
		}
	);
}

void BulletSimulator::update(
	double dt_in_seconds
	, Vector<unsigned int,2> maxPos
) {
	for(Bullet& bullet : bullets) {
		bullet.update(dt_in_seconds);
	}
	std::erase_if(bullets, [=](Bullet const& bullet) {
		return bullet.isOutOfBounds(maxPos);
	});
}


void BulletSimulator::draw(sf::RenderWindow& window) {
	for(Bullet& bullet : bullets) {
		window.draw(bullet.shape);
	}
}
