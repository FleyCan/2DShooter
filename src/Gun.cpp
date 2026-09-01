#include "Gun.hpp"
#include "Ammunition.hpp"

void Gun::updatePosition(
	Vector<float,2> position
	, float angle_radians
) {
	this->position    = position;
	this->orientation = angle_radians;
	shape.setPosition(
		position[0]
		, position[1]
	);
	shape.setRotation(angle_radians * 180 / M_PI);
}

void Gun::update(
	  BulletSimulator& simulator
	, double dt
) {
	if(!firemode->ready(dt, holdingTrigger)) {
		return;
	}

	std::optional<Ammunition> ammo_o = magazine.getAmmo();
	if(!ammo_o) {
		return;
	}

	Ammunition ammo = ammo_o.value();

	Bullet bullet{
		ammo
		, position
		+ Vector<float, 2>::polar(
			shape.getSize().x      //save gun size and make it independant from the shape
			, orientation
		)
		, Vector<float, 2>::polar(
			ammo.speed
			, orientation
		)
	};

	simulator.addBullet(bullet);
}

void reload(Magazine const& magazine) { //ref , pointer, copy ???

}
