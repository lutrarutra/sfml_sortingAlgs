#include "Main.hpp"

int main()
{
	std::cout << "Hello World!" << std::endl;

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
#ifdef SFML_SYSTEM_WINDOWS
	__windowsHelper.setIcon(window.getSystemHandle());
#endif

	sf::CircleShape shape(window.getSize().x/2);
	shape.setFillColor(sf::Color::White);

	sf::Texture shapeTexture;
	shapeTexture.loadFromFile("content/sfml.png");
	shape.setTexture(&shapeTexture);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
