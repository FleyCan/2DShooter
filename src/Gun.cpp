#include "Gun.hpp"

void Gun::update(
	Vector<float,2> position
	, float angle_radians
	, double dt
) {
	counter += dt;
	this->position    = position;
	this->orientation = angle_radians;
	shape.setPosition(
		position[0]
		, position[1]
	);
	shape.setRotation(angle_radians * 180 / M_PI);
}

void Gun::cycleFiremode() {
	if(firemode == Firemode::SEMI) {
		firemode = Firemode::BURST;
	} else if(firemode == Firemode::BURST) {
		firemode = Firemode::FULL;
	} else if(firemode == Firemode::FULL) {
		firemode = Firemode::SEMI;
	}
}

void Gun::shoot(BulletSimulator& simulator) {

	if(holdingTrigger) {
		if(firemode == Gun::Firemode::SEMI) {
			if(holdingTrigger != lastState) {
				if(RPM / 60 * counter > 1) {
					simulator.addBullet(
						position
						+ Vector<float, 2>::polar(
							shape.getSize().x
							, orientation
						)
						, Vector<float, 2>::polar(
							1028.0f
							, orientation
						)
					);
				counter = 0;
				}
			}
		}

		if(firemode == Gun::Firemode::FULL) {
			if(RPM / 60 * counter > 1) {
				simulator.addBullet(
					position
					+ Vector<float, 2>::polar(
						shape.getSize().x
						, orientation
					)
					, Vector<float, 2>::polar(
						1028.0f
						, orientation
					)
				);
				counter = 0;
			}
		}

		if(firemode == Gun::Firemode::BURST) {
			if((RPM / 60 * counter) > (1 * burstcount)) {
				simulator.addBullet(
					position
					+ Vector<float, 2>::polar(
						shape.getSize().x
						, orientation
					)
					, Vector<float, 2>::polar(
						1028.0f
						, orientation
					)
				);
				++bulletcounter;
				if(bulletcounter == burstcount) {
					counter = 0;
					bulletcounter = 0;
				}
			}
		}
	}

	lastState = holdingTrigger;
}
