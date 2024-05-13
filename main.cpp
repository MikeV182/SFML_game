#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1600,1200), "CUBE CHASER - WAVE: 1 - TIME LEFT: 15 - WAVES LEFT: 10", sf::Style::Default);

	sf::RectangleShape player(sf::Vector2f(150.0f,150.0f));
	player.setFillColor(sf::Color::Green);
	player.setOrigin(75.0f,75.0f);
	player.setPosition(800,600);
	
	while (window.isOpen()) {

		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::Closed :
					std::cout << "Window is closed";
					window.close();
					break;
			}
		}

		sf::Vector2f pos = player.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && pos.x + 75.0f < 1600.0f) {
			player.move(+0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && pos.x - 75.0f > 0.0f) {
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && pos.y - 75.0f > 0.0f) {
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && pos.y + 75.0f < 1200.0f) {
			player.move(0.0f, +0.1f);
		}

		window.clear(sf::Color::Black);

		window.draw(player);
		window.display();
	}
	return 0;
}