#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <chrono>

#define SCREEN_W 1600
#define SCREEN_H 1200
#define FONT_SIZE 120
#define QUBE_SIZE 150.0f
#define QUBE_ORIGIN (QUBE_SIZE / 2)
#define PLAYER_SPEED 0.15f
#define ENEMY_SPEED (PLAYER_SPEED / 3)
#define ROUND_TIME 15
#define ROUNDS_TOTAL 10

sf::RectangleShape CreatePlayer() {
	sf::RectangleShape player(sf::Vector2f(QUBE_SIZE,QUBE_SIZE));
	player.setFillColor(sf::Color::Green);
	player.setOrigin(QUBE_ORIGIN,QUBE_ORIGIN);
	player.setPosition(SCREEN_W / 2,SCREEN_H / 2);
	return player;
}

sf::RectangleShape CreateEnemy() {
	sf::RectangleShape enemy(sf::Vector2f(QUBE_SIZE,QUBE_SIZE));
	enemy.setFillColor(sf::Color::Red);
	enemy.setOrigin(QUBE_ORIGIN,QUBE_ORIGIN);
	enemy.setPosition(1300, 1000);
	return enemy;
}

sf::Vector2f EnemyMove(sf::RectangleShape enemy, sf::Vector2f posPlayer, sf::Vector2f posEnemy) {
	if (posEnemy.x > posPlayer.x) {
		enemy.move(-ENEMY_SPEED, 0.0f);
	}
	if (posEnemy.x < posPlayer.x) {
		enemy.move(+ENEMY_SPEED, 0.0f);
	}
	if (posEnemy.y > posPlayer.y) {
		enemy.move(0.0f, -ENEMY_SPEED);
	}
	if (posEnemy.y < posPlayer.y) {
		enemy.move(0.0f, +ENEMY_SPEED);
	}

	return enemy.getPosition();
}

bool collisionDetect(sf::RectangleShape player, sf::RectangleShape enemy) {
	if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
		return true;
	}

	else return false;
}

sf::Text gameStatus(const sf::Font& font, std::string line) {
	sf::Text txt;
	txt.setFont(font);
	txt.setString(line);
	txt.setCharacterSize(FONT_SIZE);
	txt.setFillColor(sf::Color::Cyan);
	txt.setStyle(sf::Text::Bold);
	txt.setPosition(SCREEN_W / 2, SCREEN_H / 2);

	return txt;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_W,SCREEN_H), "CUBE CHASER - WAVE: 0 - TIME LEFT: 15 - WAVES LEFT: 10", sf::Style::Default);

	sf::RectangleShape player = CreatePlayer();
	sf::RectangleShape enemy = CreateEnemy();

	sf::Font font;
	if (!font.loadFromFile("fonts/Freedom.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return -1;
	}
	
	int curWave = 0, seconds = ROUND_TIME, suspended = 0;
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

		int nextRound = 0, timeRound = ROUND_TIME;
		while (!nextRound && !suspended && window.isOpen() && (ROUNDS_TOTAL - curWave != 0)) {

			while (window.pollEvent(evnt)) {
				switch (evnt.type) {
				case sf::Event::Closed:
					std::cout << "Window is closed\n";
					window.close();
					break;
				}
			}
			
			std::ostringstream oss;
			oss << "CUBE CHASER - WAVE: " << curWave << " - TIME LEFT: " << timeRound << " - WAVES LEFT: " << ROUNDS_TOTAL - curWave;
			window.setTitle(oss.str());

			sf::Vector2f posPlayer = player.getPosition();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && posPlayer.x + QUBE_ORIGIN < SCREEN_W) {
				player.move(+PLAYER_SPEED, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && posPlayer.x - QUBE_ORIGIN > 0.0f) {
				player.move(-PLAYER_SPEED, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && posPlayer.y - QUBE_ORIGIN > 0.0f) {
				player.move(0.0f, -PLAYER_SPEED);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && posPlayer.y + QUBE_ORIGIN < SCREEN_H) {
				player.move(0.0f, +PLAYER_SPEED);
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
			timeRound = ROUND_TIME * (curWave+1) - static_cast<int>(duration.count());
			if (duration.count() >= seconds) {
				nextRound = 1;
				seconds += ROUND_TIME;
			}

		}

		if (suspended) {
			sf::Text text = gameStatus(font, "You lose");
			window.clear(sf::Color::Black);
			window.draw(text);
			window.display();
		}

		else if (ROUNDS_TOTAL - curWave == 0 && !suspended) {
			sf::Text text = gameStatus(font, "You win");
			window.clear(sf::Color::Black);
			window.draw(text);
			window.display();
		}

		else curWave += 1;

	}

	return 0;
}