#include "Bar.h"

Bar::Bar()
{
	this->n = 0;
}

Bar::Bar(int n)
{
	this->n = n;
}

Bar::Bar(int _w, int _n, int _dy)
{
	this->w = _w;
	this->n = _n;
	this->dy = _dy;

	this->rect = new sf::RectangleShape(sf::Vector2f(w, dy * n));
	this->rect->setOrigin(0, dy * n);
	this->rect->setFillColor(sf::Color(175, 205, 255));
	this->rect->setOutlineThickness(1.0f);
	this->rect->setOutlineColor(sf::Color::Black);
}

void Bar::setN(int n)
{
	this->n = n;
	this->rect->setSize(sf::Vector2f(w, dy * n));
	this->rect->setOrigin(0, dy * n);
}

int Bar::getN()
{
	return this->n;
}

Bar::~Bar()
{
	delete this->rect;
}

sf::RectangleShape *Bar::getRect()
{
	return this->rect;
}