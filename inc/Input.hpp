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

#include <ostream>
#include <functional>
#include <cstdint>
#include <algorithm>

#include "Controller.hpp"

struct Input {

	std::uint16_t up   ;
	std::uint16_t down ;
	std::uint16_t left ;
	std::uint16_t right;

	Input() = default;

	static std::function<void(sf::Event const&, Input&)> captureWASD;

	static std::function<void(sf::Event const&, Input&)> captureArrowKeys;

	static std::function<void(sf::Event const&, Input&)> captureControllerXY;

	friend
	std::ostream& operator<<(std::ostream& os, Input input) {
		os << "up = "    << input.up    << '\n';
		os << "down = "  << input.down  << '\n';
		os << "left = "  << input.left  << '\n';
		os << "right = " << input.right << '\n';

		return os;
	}
};
