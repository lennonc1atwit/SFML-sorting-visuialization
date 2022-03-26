#include "Bar.h"

Bar::Bar()
{

}

Bar::Bar(int dx, int dy, int n)
{
	_dx = dx;
	_dy = dy;
	_v = n;

	// Get handle of rect
	_pRect = new sf::RectangleShape(sf::Vector2f(_dx, _dy * _v));
	// Set origin to bottom left corner of rect
	_pRect->setOrigin(sf::Vector2f(0, _dy * _v));
	_pRect->setFillColor(sf::Color::Black);
	_pRect->setOutlineColor(sf::Color::White);
	_pRect->setOutlineThickness(1);
}

Bar::~Bar()
{
	delete _pRect;
}

int Bar::getWidth()
{
	return _dx;
}

int Bar::getHeight()
{
	return _dy * _v;
}

int Bar::getValue()
{
	return _v;
}

void Bar::setValue(int v)
{
	_v = v;

	// Update size and origin
	_pRect->setSize(sf::Vector2f(_dx, _dy * _v));
	_pRect->setOrigin(sf::Vector2f(0, _dy * _v));

}

sf::RectangleShape* Bar::getRectPtr()
{
	return _pRect;
}
