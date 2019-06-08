#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>

#include "Main.hpp"
#include "Bar.h"

#define LOG(x) std::cout << x << std::endl

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
	for (int i = 0; i < barsCount; ++i)
	{
		bars[i]->getRect()->setPosition(((window.getSize().x) / barsCount) * (i), window.getSize().y);
	}
	window.clear(sf::Color(120, 125, 135));
	for (int i = 0; i < barsCount; ++i)
	{
		window.draw(sf::RectangleShape(*(bars[i]->getRect())));
	}
	window.display();
}

int quickSortPartition(Bar *a[], int lowI, int highI)
{
	int pivot = a[highI]->getN();
	int i = lowI - 1;

	for (int j = lowI; j <= highI - 1; ++j)
	{
		if (a[j]->getN() <= pivot)
		{
			i++;
			swap(a, i, j);
			usleep(30000);
		}
	}
	swap(a, i + 1, highI);
	usleep(10000);
	return i + 1;
}

void quickSort(Bar *a[], int lowI, int highI)
{
	if (lowI < highI)
	{
		int pi = quickSortPartition(a, lowI, highI);

		quickSort(a, lowI, pi - 1);
		quickSort(a, pi + 1, highI);
	}
}

void sortingThread(Bar *bars[], int barsCount)
{
	quickSort(bars, 0, barsCount - 1);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Algorithms", sf::Style::Close);

	const int barsCount = 250;
	Bar *bars[barsCount];

	auto swapTime = std::chrono::milliseconds(500);
	auto dt = std::chrono::high_resolution_clock::now();

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

	std::thread sort(&sortingThread, bars, barsCount);

	sf::Event event;

	while (window.isOpen())
	{
		if (std::chrono::high_resolution_clock::now() > dt)
		{
			//std::cout << "Hello" << std::endl;
			dt = std::chrono::high_resolution_clock::now() + swapTime;
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		renderBars(bars, barsCount, window);

	}

	for (int i = 0; i < barsCount; ++i)
	{
		delete bars[i];
	}

	return 0;
}
