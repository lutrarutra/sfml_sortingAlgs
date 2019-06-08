#include <SFML/Graphics.hpp>

class Bar
{
public:
	Bar();
	Bar(int w, int h, int n);
	~Bar();
	sf::RectangleShape* getRect();
	int getN();
private:
	int w, h, n;
	sf::RectangleShape* rect;

};