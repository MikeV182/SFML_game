#include <iostream>
#include <SFML/Graphics.hpp>

sf::RectangleShape CreateEnemy() {
	sf::RectangleShape enemy(sf::Vector2f(150.0f, 150.0f));
	enemy.setFillColor(sf::Color::Red);
	enemy.setOrigin(75.0f, 75.0f);
	enemy.setPosition(1300, 1000);
	return enemy;
}

sf::Vector2f EnemyMove(sf::RectangleShape enemy, sf::Vector2f posPlayer, sf::Vector2f posEnemy) {
	if (posEnemy.x > posPlayer.x) {
		enemy.move(-0.05f, 0.0f);
	}
	if (posEnemy.x < posPlayer.x) {
		enemy.move(+0.05f, 0.0f);
	}
	if (posEnemy.y > posPlayer.y) {
		enemy.move(0.0f, -0.05f);
	}
	if (posEnemy.y < posPlayer.y) {
		enemy.move(0.0f, +0.05f);
	}

	return enemy.getPosition();
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1600,1200), "CUBE CHASER - WAVE: 0 - TIME LEFT: 15 - WAVES LEFT: 10", sf::Style::Default);

	sf::RectangleShape player(sf::Vector2f(150.0f,150.0f));
	player.setFillColor(sf::Color::Green);
	player.setOrigin(75.0f,75.0f);
	player.setPosition(800,600);

	sf::RectangleShape enemy = CreateEnemy();
	
	while (window.isOpen()) {

		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
				case sf::Event::Closed :
					std::cout << "Window is closed\n";
					window.close();
					break;
			}
		}

		sf::Vector2f posPlayer = player.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && posPlayer.x + 75.0f < 1600.0f) {
			player.move(+0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && posPlayer.x - 75.0f > 0.0f) {
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && posPlayer.y - 75.0f > 0.0f) {
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && posPlayer.y + 75.0f < 1200.0f) {
			player.move(0.0f, +0.1f);
		}

		window.clear(sf::Color::Black);

		sf::Vector2f posEnemy = enemy.getPosition();
		enemy.setPosition(EnemyMove(enemy, posPlayer, posEnemy));

		window.draw(enemy);
		window.draw(player);
		window.display();
	}
	return 0;
}