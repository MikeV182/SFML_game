#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <chrono>

#define FONT_SIZE 120

sf::RectangleShape CreatePlayer() {
	sf::RectangleShape player(sf::Vector2f(150.0f, 150.0f));
	player.setFillColor(sf::Color::Green);
	player.setOrigin(75.0f, 75.0f);
	player.setPosition(800, 600);
	return player;
}

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

bool collisionDetect(sf::RectangleShape player, sf::RectangleShape enemy) {
	if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
		return true;
	}

	else return false;
}

sf::Text gameLose(const sf::Font& font) {
	sf::Text txt;
	txt.setFont(font);
	txt.setString("You lose");
	txt.setCharacterSize(FONT_SIZE);
	txt.setFillColor(sf::Color::Cyan);
	txt.setStyle(sf::Text::Bold);
	txt.setPosition(1600.0f / 2.0f, 1200.0f / 2.0f);

	return txt;
}

sf::Text gameWin(const sf::Font& font) {
	sf::Text txt;
	txt.setFont(font);
	txt.setString("You Win");
	txt.setCharacterSize(FONT_SIZE);
	txt.setFillColor(sf::Color::Cyan);
	txt.setStyle(sf::Text::Bold);
	txt.setPosition(1600.0f / 2.0f, 1200.0f / 2.0f);

	return txt;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1600,1200), "CUBE CHASER - WAVE: 0 - TIME LEFT: 15 - WAVES LEFT: 10", sf::Style::Default);

	sf::RectangleShape player = CreatePlayer();
	sf::RectangleShape enemy = CreateEnemy();

	sf::Font font;
	if (!font.loadFromFile("fonts/Freedom.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return -1;
	}
	
	int curWave = 0, seconds = 15, suspended = 0;
	auto start = std::chrono::high_resolution_clock::now();
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				std::cout << "Window is closed\n";
				window.close();
				break;
			}
		}

		int nextRound = 0, timeRound = 15;
		while (!nextRound && !suspended && window.isOpen() && (10 - curWave != 0)) {

			while (window.pollEvent(evnt)) {
				switch (evnt.type) {
				case sf::Event::Closed:
					std::cout << "Window is closed\n";
					window.close();
					break;
				}
			}
			
			std::ostringstream oss;
			oss << "CUBE CHASER - WAVE: " << curWave << " - TIME LEFT: " << timeRound << " - WAVES LEFT: " << 10 - curWave;
			window.setTitle(oss.str());

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

			if (collisionDetect(player, enemy)) {
				suspended = 1;
			}

			window.draw(enemy);
			window.draw(player);
			window.display();

			auto stop = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> duration = stop - start;
			timeRound = 15 * (curWave+1) - static_cast<int>(duration.count());
			if (duration.count() >= seconds) {
				nextRound = 1;
				seconds += 15;
			}

		}

		if (suspended) {
			sf::Text text = gameLose(font);
			window.clear(sf::Color::Black);
			window.draw(text);
			window.display();
		}

		else if (10 - curWave == 0 && !suspended) {
			sf::Text text = gameWin(font);
			window.clear(sf::Color::Black);
			window.draw(text);
			window.display();
		}

		else curWave += 1;

	}

	return 0;
}