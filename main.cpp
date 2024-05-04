#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(512,512), "Close me, please", sf::Style::Close | sf::Style::Resize);

	sf::RectangleShape player1(sf::Vector2f(100.0f,150.0f));
	player1.setPosition(206.0f,206.0f);
	
	sf::Texture playerTexture;
	playerTexture.loadFromFile("OldHero.png");
	player1.setTexture(&playerTexture);

	sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 6;
	textureSize.y /= 5;

	player1.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 2, textureSize.x, textureSize.y));

	while (window.isOpen()) {	
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::Closed:
					window.close();
					break;
			}
		}

		window.draw(player1);
		window.display();
		window.clear(sf::Color::Color(157, 142, 135, 255));
	}
	return 0;
}