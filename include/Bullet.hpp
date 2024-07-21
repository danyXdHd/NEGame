#pragma once
#include <Utility.hpp>
#include <vector>
#include <Wall.hpp>

const double PI = 3.14159265358979323846;

class Bullet {
private:

public:
	int x, y;
	int angle;
	int width, height;
	int speed;


	sf::RectangleShape corner1;
	sf::RectangleShape corner2;
	sf::RectangleShape corner3;

	int Update(int px, int py, int w, int h, std::vector<Wall> Walls);

	Bullet(int xx, int yy, int aangle);
};