#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Export.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

#include "AmmoType.hpp"
#include "Magazine.hpp"
#include "Vector.hpp"
#include "BulletSimulator.hpp"

struct Gun {

	enum Firemode {
		  SEMI
		, BURST
		, FULL
	};

	Vector<float,2> position;
	float orientation;
	sf::RectangleShape shape{};
	Firemode firemode = SEMI;

	AmmoType ammotype;
	Magazine magazine;

	int burstcount = 3;
	double RPM = 0;

	double counter = 0;
	int bulletcounter = 0;

	bool holdingTrigger = false;
	bool lastState = true;

	Gun(
		 sf::RectangleShape shape
		, Vector<float,2> position
		, double RPM
		, AmmoType ammotype
		, Magazine magazine
	)
		: shape{shape}
		, position{position}
		, RPM{RPM}
		, ammotype{ammotype}
		, magazine{magazine}
	{}

	void update(
		  Vector<float,2> position
		, float angle_radians
		, double dt
	);

	void cycleFiremode();

	void shoot(BulletSimulator& simulator);

};
