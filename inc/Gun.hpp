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
#include "Firemode.hpp"

#include <memory>


struct Gun {

	Vector<float,2> position;
	float orientation;
	sf::RectangleShape shape{};

	AmmoType ammotype;
	std::unique_ptr<Magazine> magazine;
	// Magazine magazine;

	bool holdingTrigger = false;

	//std::vector<std::unique_ptr<Firemode>> firemodes; //scary | unique_pointer? | construct_at error

	Firemode* firemode;

	Gun(
		 sf::RectangleShape shape
		, Vector<float,2> position
		, double RPM
		, AmmoType ammotype
		, Magazine magazine
		, Firemode* firemode
	)
		: shape{shape}
		, position{position}
		, ammotype{ammotype}
		//, magazine{magazine}
		, firemode{firemode}
	{}

	// Gun(Gun const& other)
	// 	: position{other.position}
	// 	, orientation{other.orientation}
	// 	, shape{other.shape}
	// 	, ammotype{other.ammotype}
	// 	, firemode{other.firemode}
	// {
 //
	// }

	void updatePosition(
		  Vector<float,2> position
		, float angle_radians
	);

	void update(BulletSimulator& simulator, double dt);

	void addFiremode(Firemode* firemode);

	void cycleFiremode();

};
