#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>
#include <stdlib.h>

static sf::Vector2f normalize(sf::Vector2f& playerPos) {
	float playerLength = sqrt(playerPos.x*playerPos.x + playerPos.y* playerPos.y);

	if (playerLength) {
		return sf::Vector2f(playerPos.x / playerLength, playerPos.y / playerLength);
	}

	return playerPos;
}


int main()
{
	
	sf::RenderWindow window(sf::VideoMode({1000, 800}), "PelinCrusaderTest");
	sf::Clock clock;

	//teksture

	sf::Texture playerTexture, pelinTexture; //, backgroundTexture;
	playerTexture.loadFromFile(RESOURCES_PATH "stipeDemoni.png");
	pelinTexture.loadFromFile(RESOURCES_PATH "mPelin.png");
	

	//spriteovi
	sf::Sprite player(playerTexture);// , background(backgroundTexture);
	sf::Sprite mPelin(pelinTexture);


	//pozicija igraca
	player.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
	player.setPosition(window.getSize().x/2, window.getSize().y - playerTexture.getSize().y/2);
	player.setScale(0.7f, 0.7f);

	//pozicija boca pelina (na pocetku - kasnije se randomly pojavljaju na x osi, ali ostaju na istoj y osi)
	mPelin.setScale(0.2f, 0.2f);
	mPelin.setOrigin(pelinTexture.getSize().x / 2, pelinTexture.getSize().y / 2);
	mPelin.setPosition(window.getSize().x / 2, 0.f);
	std::vector<sf::Sprite> mPelinList(7, mPelin);

	//background.setScale(2.f, 2.f);
	//background.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
	//background.setPosition(window.getSize().x / 2, window.getSize().y / 2);


	srand(time(0)); // seed only once
	for (int i = 0; i < mPelinList.size(); i++) {
			mPelinList[i].setPosition((rand() % window.getSize().x), -200.f);
	}
	while (window.isOpen()) {

		sf::Time deltatime = clock.restart();
		float deltaTimeSec = deltatime.asSeconds();
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::Resized) {
				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}	

		sf::Vector2f playerPos(0.f, 0.f);

		float speed = 400.f;
		float pelinSpeed = 200.f;
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			playerPos += sf::Vector2f(-1.f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerPos += sf::Vector2f(1.f, 0.0f);
		}


		sf::Vector2f currentPelinPos(0.f, 0.f);
		for (int i = 0; i < mPelinList.size(); i++) {
			if (!i) {
				mPelinList[i].move(0.f, deltaTimeSec * pelinSpeed);
			}
			currentPelinPos = mPelinList[i].getPosition();
			if (currentPelinPos.y >= 50.f && i+1 < mPelinList.size()) {
				 mPelinList[i+1].move(0.f, deltaTimeSec * pelinSpeed);

			}
		}
		
		player.move(normalize(playerPos)*deltaTimeSec * speed);

		//window.draw(background);

		window.clear();
		for (int i = 0; i < mPelinList.size(); i++) {
			window.draw(mPelinList[i]);
		}
		
		window.draw(player);
		
		window.display();
		
	}
	
	return 0;
}