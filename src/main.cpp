#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

#include <iostream>
#include <chrono>
#include <vector>
#include <memory>

#include "Vector.hpp"
#include "Person.hpp"
#include "Input.hpp"
#include "Gun.hpp"
#include "BulletSimulator.hpp"

double radiantToDegree = 180/M_PI;

struct Scene {
	std::vector<std::shared_ptr<sf::Shape>> shapes;

	Scene() {
		auto red = std::make_shared<sf::CircleShape>(50.0f);
		red->setOrigin(50.0f,50.0f);
		red->setFillColor(sf::Color::Red);
		red->setPosition(200.0f,0.0f);

		auto green = std::make_shared<sf::CircleShape>(50.0f);
		green->setOrigin(50.0f,50.0f);
		green->setFillColor(sf::Color::Green);
		green->setPosition(0.0f,200.0f);

		auto origin = std::make_shared<sf::CircleShape>(50.0f);
		origin->setOrigin(50.0f,50.0f);
		origin->setFillColor(sf::Color::White);
		origin->setPosition(0.0f,0.0f);

		shapes.push_back(red);
		shapes.push_back(green);
		shapes.push_back(origin);
	}

	void draw(sf::RenderWindow& window) {
		for(auto& shape : shapes) {
			window.draw(*shape);
		}
	}

};

int main() {

	sf::RenderWindow window;
	window.create(sf::VideoMode{1024,1024},"window");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Event event;
	Input input{};


	sf::RectangleShape rectangle{sf::Vector2f{60.0f,20.0f}};
	rectangle.setOrigin(sf::Vector2f{0.0f,10.0f});
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setOutlineThickness(5.0f);

	Gun gun{rectangle,{512,512},600};


	sf::CircleShape circle{50.0f};
	circle.setOrigin(sf::Vector2f{50.0f,50.0f});
	circle.setFillColor(sf::Color::Blue);

	Person player{{512,512},2,{1024,1024},circle,gun};


	circle.setFillColor(sf::Color::Red);

	Person enemy{{900,900},2,{1024,1024},circle,gun};
	enemy.gun.firemode = Gun::Firemode::FULL;

	sf::Vector2i mouse_position{};

	using clock_t = std::chrono::steady_clock;
	clock_t::time_point last_time = clock_t::now();

	Vector<float,2> mouse_vector;

	double enemy_counter = 0;

	BulletSimulator bulletSimulator;

	//Scene scene;

	while(window.isOpen()) {
		while (window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				window.close();
			}
			if(event.type == sf::Event::Resized)
			{
				sf::FloatRect view(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(view));
			}
			if(event.type == sf::Event::MouseMoved) {
				mouse_position.x = event.mouseMove.x;
				mouse_position.y = event.mouseMove.y;
			}
			
			if(event.type == sf::Event::MouseButtonPressed) {
				player.gun.holdingTrigger = true;
			}
			if(event.type == sf::Event::MouseButtonReleased) {
				player.gun.holdingTrigger = false;
			}
			if(event.type == sf::Event::KeyPressed) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::V)) {
					player.gun.cycleFiremode();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) {
					enemy.gun.holdingTrigger = !enemy.gun.holdingTrigger;
				}
			}
		}

		Input::captureArrowKeys(event,input);

		enemy.gun.shoot(bulletSimulator);

		player.gun.shoot(bulletSimulator);

		Vector<float,2> mouse_vector {
			  static_cast<float>(mouse_position.x)
			, static_cast<float>(mouse_position.y)
		};

		clock_t::time_point now = clock_t::now();
		std::chrono::duration<double> delta = now - last_time;
		double dt_in_seconds = delta.count();
		enemy_counter += dt_in_seconds;
		last_time = now;

		std::cout << dt_in_seconds << '\n';
		std::cout << input << '\n';
		std::cout << player.position << '\n';
		std::cout << mouse_vector << '\n';
		std::cout << "degree = "
		<<  radiantToDegree * (mouse_vector - player.position).orientation()
		<< '\n';
		std::cout << "gun rotation" << player.gun.shape.getRotation() << '\n';
		std::cout << "number of bullets = " << bulletSimulator.bullets.size() << '\n';

		player.update(
			  Vector<unsigned int,2> {
				  window.getSize().x
				, window.getSize().y
			  }
			, player.processInput(input, dt_in_seconds)
			, dt_in_seconds
		);

		player.gun.update(
			  player.position
			, (mouse_vector - player.position).orientation()
			, dt_in_seconds
		);

		enemy.update(
			Vector<unsigned int,2> {
				window.getSize().x
				, window.getSize().y
			}
			, enemy.position
			, dt_in_seconds
		);

		enemy.gun.update(
			  enemy.position
			, (player.position - enemy.position).orientation()
			, dt_in_seconds
		);

		bulletSimulator.update(
			  dt_in_seconds
			, Vector<unsigned int,2>{
				  window.getSize().x
				, window.getSize().y
			}
		);

		window.clear(sf::Color::Black);

		bulletSimulator.draw(window);

		//scene.draw(window);
		window.draw(player.shape);
		window.draw(player.gun.shape);

		window.draw(enemy.shape);
		window.draw(enemy.gun.shape);

		window.display();
	}

	return 0;
}
