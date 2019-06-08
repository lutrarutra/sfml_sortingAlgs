#include <SFML/Graphics.hpp>

class Bar
{
public:
	Bar();
	Bar(int n);
	Bar(int w, int h, int n);
	~Bar();
	sf::RectangleShape *getRect();
	int getN();
	void setN(int n);

private:
	int w, h, n;
	sf::RectangleShape *rect;
};