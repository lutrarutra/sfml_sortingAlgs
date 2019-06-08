#include <math.h>
#include "Main.hpp"
#include "Bar.h"

void swap(Bar *a[], int i, int j)
{
	Bar *temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void shuffle(Bar *a[], int arraySize)
{
	srand(time(NULL));
	for (int i = arraySize - 1; i > 0; --i)
	{
		int j = rand() % i + 1;
		swap(a, i, j);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Algorithms", sf::Style::Close);

	sf::Event event;

	int barsCount = 250;
	Bar *bars[barsCount];

	int dx = ((window.getSize().x) / barsCount);
	int dh = (window.getSize().y / barsCount);

	for (int i = 0; i < barsCount; ++i)
	{
		bars[i] = new Bar(dx, dh * (i + 1), 0);
	}

	shuffle(bars, barsCount);

	for (int i = 0; i < barsCount; ++i)
	{
		bars[i]->getRect()->setPosition(dx * (i +1), window.getSize().y);
	}

	window.clear(sf::Color(120, 125, 135));
	for (int i = 0; i < barsCount; ++i)
	{
		window.draw(sf::RectangleShape(*(bars[i]->getRect())));
	}
	window.display();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	for (int i = 0; i < barsCount; ++i)
	{
		delete bars[i];
	}

	return 0;
}
