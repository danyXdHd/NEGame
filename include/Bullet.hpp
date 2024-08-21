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

	int damage;
	int pierce;

	float sinc, cosc;

	sf::Sprite sprite;
	sf::RectangleShape WTF0;
	sf::RectangleShape WTF1;
	sf::RectangleShape WTF2;
	sf::RectangleShape WTF3;

	bool Update(int px, int py, int w, int h, float dTime, std::vector<Wall>& Walls);

	bool isColiding(int xx, int yy, int ww, int hh) const;

	Bullet(int xx, int yy, float aangle, int dmg, int prc);
};