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

#include "Vector.hpp"


struct Bullet {

	Vector<float,2> position;
	Vector<float,2> velocity;

	sf::CircleShape shape{10.0f};

	Bullet(
		  Vector<float,2> position
		, Vector<float,2> velocity
	)
		: position{position}
		, velocity{velocity}
	{
		shape.setFillColor(sf::Color::Yellow);
		shape.setOrigin(10.0f,10.0f);
		shape.setPosition(
			  position[0]
			, position[1]
		);
	}

	void update(double dt) {
		position += velocity * dt;

		shape.setPosition(
			  position[0]
			, position[1]
		);
	}

	bool isOutOfBounds(Vector<unsigned int,2> maxPos) const {
		if(position[0] < 0) return true;
		if(position[1] < 1) return true;
		if(position[0] > maxPos[0]) return true;
		if(position[1] > maxPos[1]) return true;
		return false;
	}

};
