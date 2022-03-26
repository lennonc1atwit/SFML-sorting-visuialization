#include <SFML/Graphics.hpp>
#include "Bar.h"
#include "Algorithms.h"

#include <iostream>
#include <Windows.h>
#include <thread>

void updateBars(Bar* bar_arr[], int num_arr[], int size)
{
	// Set bars to match num array state
	for (int i = 0; i < size; i++) {
		bar_arr[i]->setValue(num_arr[i]);
	}
}

void drawBars(Bar* bar_arr[], int size, sf::RenderWindow &window)
{
	// Update position and display color
	for (int i = 0; i < size; i++) {
		bar_arr[i]->getRectPtr()->setPosition(window.getSize().x / size * i, window.getSize().y);
		window.draw(*bar_arr[i]->getRectPtr());
	}
}

int main()
{
	const int num_elements = 250;

	int num_array[num_elements];
	Bar* bar_array[num_elements];

	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML sorting visuialization!");
	sf::View view = window.getDefaultView();

	int dx = window.getSize().x / num_elements;
	int dy = window.getSize().y / num_elements;

	for (int i = 0; i < num_elements; i++) {
		bar_array[i] = new Bar(dx, dy, i);
		num_array[i] = i;
	}

	// Shuffle sorting array and update bars
	Algorithms::shuffle(num_array, num_elements);
	updateBars(bar_array, num_array, num_elements);

	// Start a sort on a new thread
	std::thread sorting_thread(&Algorithms::selectionSort, bar_array, num_array, num_elements);
	//std::thread sorting_thread(&Algorithms::insertionSort, bar_array, num_array, num_elements);
	
	while (window.isOpen())
	{
		// Event handling
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
		}

		window.clear(sf::Color(51,51,255));

		updateBars(bar_array, num_array, num_elements);
		drawBars(bar_array, num_elements, window);

		window.display();
	}

	sorting_thread.join();
}