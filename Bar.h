#pragma once
#include <SFML/Graphics.hpp>

class Bar
{
public:
	Bar();
	Bar(int dx, int dy, int n);
	~Bar();

	int getWidth();
	int getHeight();
	int getValue();
	void setValue(int v);
	void setColor(sf::Color clr);

	sf::RectangleShape* getRectPtr();

private:
	int _dx;
	int _dy;
	int _v;

	sf::RectangleShape* _pRect;
};

