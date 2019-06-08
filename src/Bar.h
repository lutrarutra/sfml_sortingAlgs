#include <SFML/Graphics.hpp>

class Bar
{
public:
	Bar();
	Bar(int n);
	Bar(int w, int n, int _dy);
	~Bar();
	sf::RectangleShape *getRect();
	int getN();
	void setN(int n);


private:
	int w, n, dy;
	sf::RectangleShape *rect;
};