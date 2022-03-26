#pragma once
#include <SFML/Graphics.hpp>
#include "Bar.h"

class MainApp
{
public:
	void Init();
	void Quit();
private:
	void Run(); // Main app loop 
	void HandleEvent(sf::Event event);
	void Update();
	void Draw();

	void Shuffle();

	sf::RenderWindow _window;

	// sorting params
	unsigned int _num_elements = 5;
	std::vector<Bar> _element_array;

	// display params

};

