#include <math.h>
#include <chrono>
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

void renderBars(Bar *bars[], int barsCount, sf::RenderWindow &window)
{
	window.clear(sf::Color(120, 125, 135));
	for (int i = 0; i < barsCount; ++i)
	{
		window.draw(sf::RectangleShape(*(bars[i]->getRect())));
	}
	window.display();
}

int quickSortStep(Bar *a[], int arraySize, int startIndex, int pivotIndex)
{
	int ri = -1; //first smaller num than pivot from right
	int li = -1; //first bigger num than pivot from left

	for (int i = startIndex; i < pivotIndex; ++i)
	{
		if (a[i]->getN() > a[pivotIndex]->getN() && li == -1)
			li = i;
		if (a[pivotIndex - i - 1]->getN() < a[pivotIndex]->getN() && ri == -1)
			ri = pivotIndex - i - 1;
	}

	if (ri < li && ri != -1)
	{
		std::cout << "changing pivot ri: " << ri << " li: " << li << std::endl;
		swap(a, li, pivotIndex);
		pivotIndex--;
		return pivotIndex;
	}
	std::cout << "swapping ri and li " << ri << " " << li << std::endl;

	if (li == -1 && ri != -1)
	{
		pivotIndex--;
		return pivotIndex;
	}

	if (ri != -1 && li != -1)
		swap(a, ri, li);
	return pivotIndex;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Algorithms", sf::Style::Close);

	auto swapTime = std::chrono::milliseconds(500);
	auto dt = std::chrono::high_resolution_clock::now();

	int barsCount = 10;
	Bar *bars[barsCount];

	int dx = ((window.getSize().x) / barsCount);
	int dh = (window.getSize().y / barsCount);

	for (int i = 0; i < barsCount; ++i)
	{
		bars[i] = new Bar(dx, dh * (i + 1), i);
	}

	shuffle(bars, barsCount);

	for (int i = 0; i < barsCount; ++i)
	{
		bars[i]->getRect()->setPosition(dx * (i), window.getSize().y);
	}

	renderBars(bars, barsCount, window);

	int pivotIndex = barsCount - 1;

	sf::Event event;

	while (window.isOpen())
	{
		if (std::chrono::high_resolution_clock::now() > dt)
		{
			//std::cout << "Hello" << std::endl;
			pivotIndex = quickSortStep(bars, barsCount, 0, pivotIndex);
			renderBars(bars, barsCount, window);
			dt = std::chrono::high_resolution_clock::now() + swapTime;
		}

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
