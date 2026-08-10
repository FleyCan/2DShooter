#include "Input.hpp"

int max = 32;

std::function<void(sf::Event const& event, Input& input)>
Input::captureArrowKeys = [](sf::Event const& event,Input& input) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up) && input.up < max) {
		++input.up;
	} else if(input.up > 0) {
		--input.up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down) && input.down < max) {
		++input.down;
	} else if(input.down > 0) {
		--input.down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) && input.left < max) {
		++input.left;
	} else if(input.left > 0) {
		--input.left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) && input.right < max) {
		++input.right;
	} else if(input.right > 0) {
		--input.right;
	}
};

std::function<void(sf::Event const&, Input&)>
Input::captureWASD = [](sf::Event const& event,Input& input) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
		input.up = true;
	} else {
		input.up = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
		input.down = true;
	} else {
		input.down = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		input.left = true;
	} else {
		input.left = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		input.right = true;
	} else {
		input.right = false;
	}
};


std::function<void(sf::Event const&, Input&)>
captureControllerXY = [](sf::Event const& event,Input& input) {
	Controller::controllerDebug(event);
	if((event.type == sf::Event::JoystickButtonPressed
		&& event.joystickButton.button == 3))
	{
		input.up = true;
	} else {
		input.up = false;
	}

	if((event.type == sf::Event::JoystickButtonPressed
		&& event.joystickButton.button == 0))
	{
		input.up = true;
	} else {
		input.up = false;
	}

	if((event.type == sf::Event::JoystickButtonPressed
		&& event.joystickButton.button == 2))
	{
		input.up = true;
	} else {
		input.up = false;
	}

	if((event.type == sf::Event::JoystickButtonPressed
		&& event.joystickButton.button == 1))
	{
		input.up = true;
	} else {
		input.up = false;
	}
};
