#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(512,512), "Close me, please", sf::Style::Close | sf::Style::Resize);
	
	sf::RectangleShape player1(sf::Vector2f(150.0f,150.0f));
	player1.setFillColor(sf::Color::Green);
	player1.setOrigin(sf::Vector2f(75.0f,75.0f));

	unsigned int width;
	unsigned int height;

	while (window.isOpen()) {	
		sf::Event evnt;
		sf::Vector2u size;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					size = window.getSize();
					width = size.x;
					height = size.y;
					std::cout << width << " " << height << std::endl;
					break;
				case sf::Event::TextEntered:
					if (evnt.text.unicode < 128) { // in order to not work with CTRL and other specific inputs
						char smb = evnt.text.unicode;
						std::cout << smb;
					}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player1.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player1.move(0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			player1.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player1.move(0.0f, 0.1f);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			player1.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		}

		window.draw(player1);
		window.display();
		window.clear(sf::Color::Black);
	}
	return 0;
}