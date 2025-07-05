#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
	
	sf::RenderWindow window(sf::VideoMode({800, 800}), "Moj Prozorcic");
	//moze a i netriba sf default, samo sluzi za resizanje prozorea
	window.setVerticalSyncEnabled(true);
	sf::CircleShape shape(150.0f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//potrebno jer nakon svakog crtanja necega / ili teksture triba biti refreshano
		//inace ce sve biti iza i nece se updateati
		window.clear(sf::Color::Black);
		window.draw(shape);
		// uzme ono sto je bilo nacrtano, i displaya to na ekran
		window.display();
	}
	
	return 0;
}