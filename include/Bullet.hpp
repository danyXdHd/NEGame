#pragma once
#include <Utility.hpp>
#include <vector>
#include <Wall.hpp>

class Bullet {
private:

public:
	float x, y;
	float dx, dy;
	float width, height;
	int speed;
	float angle;

	float sinc, cosc;

	sf::Sprite sprite;
	sf::RectangleShape WTF0;
	sf::RectangleShape WTF1;
	sf::RectangleShape WTF2;
	sf::RectangleShape WTF3;

	bool Update(int px, int py, int w, int h, float dTime, std::vector<Wall>& Walls);

	Bullet(int xx, int yy, float aangle);
};