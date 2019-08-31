#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>

#include "Bar.h"

#define LOG(x) std::cout << x << std::endl

void swap(int *a, int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void shuffle(int *a, int arraySize)
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

void cpy_arr(Bar *src[], Bar *dest[], int start, int end)
{
	for (int i = start; i < end; ++i)
	{
		dest[i - start] = new Bar(src[i]->getN());
	}
}

void merge(int *arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			usleep(10000);
			i++;
		}
		else
		{
			arr[k] = R[j];
			usleep(10000);
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		usleep(10000);
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		usleep(10000);
		j++;
		k++;
	}
}

void mergeSort(int *arr, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

int quickSortPartition(int *a, int lowI, int highI)
{
	int pivot = a[highI];
	int i = lowI - 1;

	for (int j = lowI; j <= highI - 1; ++j)
	{
		if (a[j] <= pivot)
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

void quickSort(int *numbers, int lowI, int highI)
{
	if (lowI < highI)
	{
		int pi = quickSortPartition(numbers, lowI, highI);

		quickSort(numbers, lowI, pi - 1);
		quickSort(numbers, pi + 1, highI);
	}
}

void insertionSort(int *arr, int numCount)
{
	for (int i = 0; i < numCount; ++i)
	{
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j)
		{
			swap(arr, j, j - 1);
			usleep(5000);
		}
	}
}

void bubbleSort(int *arr, int numCount)
{
	bool swapped;
	do
	{
		swapped = false;
		for (int i = 1; i < numCount; ++i)
		{
			if (arr[i - 1] > arr[i])
			{
				swap(arr, i, i - 1);
				//swapped = true;
				usleep(5000);
			}
		}

	} while (!swapped);
}

void updateBars(Bar *bars[], int *numbers, int numCount)
{
	for (int i = 0; i < numCount; ++i)
	{
		bars[i]->setN(numbers[i]);
	}
}

int main()
{
	const int numCount = 250;

	Bar *bars[numCount];
	int numbers[numCount];

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Algorithms", sf::Style::Close);
	int dx = ((window.getSize().x) / numCount);
	int dy = (window.getSize().y / numCount);

	for (int i = 0; i < numCount; ++i)
	{
		bars[i] = new Bar(dx, i, dy);
		numbers[i] = i;
	}

	// Make number order random
	shuffle(numbers, numCount);
	// Update new random order to bars to their corresponding n-values
	updateBars(bars, numbers, numCount);

	// Update bars visually to random order
	for (int i = 0; i < numCount; ++i)
	{
		bars[i]->getRect()->setPosition(dx * (i), window.getSize().y);
	}

	// Show them
	renderBars(bars, numCount, window);

	// Different Algorithms
	std::thread sort(&quickSort, numbers, 0, numCount - 1);
	//std::thread sort(&mergeSort, numbers, 0, numCount - 1);
	//std::thread sort(&insertionSort, numbers, numCount);
	//std::thread sort(&bubbleSort, numbers, numCount);

	sf::Event event;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		updateBars(bars, numbers, numCount);
		renderBars(bars, numCount, window);
	}

	for (int i = 0; i < numCount; ++i)
	{
		delete bars[i];
	}

	return 0;
}
