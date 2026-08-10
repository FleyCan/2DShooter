#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

#include <cmath>

#include "Vector.hpp"
#include "Input.hpp"
#include "Gun.hpp"

struct Person {

	Vector<float,2> position;
	double          speed;
	sf::CircleShape shape{};

	Vector<unsigned int,2> maxPosition;

	Gun gun;

	Person(
		  Vector<float,2> position
		, double speed
		, Vector<unsigned int,2> maxPosition
		, sf::CircleShape shape
		, Gun gun
	)
		: position{position}
		, speed{speed}
		, maxPosition{maxPosition}
		, shape{shape}
		, gun{gun}
	{}

	// Person(float x, float y)
	// 	: position{{x,y}}
	// {}

	Vector<float,2> processInput(Input input, double dt);

	void update(
		  Vector<unsigned int,2> maxPosition
		, Vector<float,2> targetPosition
		, double dt
	);
};
