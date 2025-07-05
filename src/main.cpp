#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
	
	sf::Window window(sf::VideoMode({800, 800}), "Moj Prozorcic", sf::Style::Default);
	//moze a i netriba sf default, samo sluzi za resizanje prozorea
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			

		}
		
	}
	
	return 0;
}