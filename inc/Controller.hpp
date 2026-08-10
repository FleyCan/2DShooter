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

#include <iostream>

struct Controller {

	static void controllerDebug(sf::Event event) {
		if (event.type == sf::Event::JoystickMoved)
		{
			auto inspect = [&](sf::Joystick::Axis axis, char const* name) {
				if (event.joystickMove.axis == axis)
				{
					std::cout << name << " axis moved!" << '\n';
					std::cout << "joystick id: " << event.joystickMove.joystickId << '\n';
					std::cout << "new position: " << event.joystickMove.position << '\n';
				}
			};
			inspect(sf::Joystick::Axis::X, "X");
			inspect(sf::Joystick::Axis::Y, "Y");
			inspect(sf::Joystick::Axis::Z, "Z");
			inspect(sf::Joystick::Axis::R, "R");
			inspect(sf::Joystick::Axis::U, "U");
			inspect(sf::Joystick::Axis::V, "V");
			inspect(sf::Joystick::Axis::PovX, "PovX");
			inspect(sf::Joystick::Axis::PovY, "PovY");
		}
		if (event.type == sf::Event::JoystickButtonPressed)
		{
			std::cout << "joystick button pressed!" << '\n';
			std::cout << "joystick id: " << event.joystickButton.joystickId << '\n';
			std::cout << "button: " << event.joystickButton.button << '\n';
		}
	}

};
