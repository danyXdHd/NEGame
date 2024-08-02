#include "Bullet.hpp"

int Bullet::Update(int px, int py, int w, int h, std::vector<Wall> Walls)
{
	std::pair<double, double> newPos =  calculatePointInDirection(x, y, angle, speed);
	x = newPos.first;
	y = newPos.second;

	corner1.setSize(sf::Vector2f(16, 16));
	corner1.setPosition(x + width * cos(angle * PI / 180), y);
	corner1.setFillColor(sf::Color(255, 0, 0));


	corner1.setSize(sf::Vector2f(16, 16));
	corner2.setPosition(x, y + height * sin(angle * PI / 180));
	corner2.setFillColor(sf::Color(0, 255, 0));


	corner1.setSize(sf::Vector2f(16, 16));
	corner3.setPosition(x + width * cos(angle * PI / 180), y + height * sin(angle * PI / 180));
	corner3.setFillColor(sf::Color(0, 0, 255));

	bool ok = false;
	/*for (int i = 0; i < Walls.size(); i++)
		if ((x < (Walls[i].x + Walls[i].width) * Walls[i].TextureWidth &&
			x > Walls[i].x * Walls[i].TextureWidth &&
			y < (Walls[i].y + Walls[i].height) * Walls[i].TextureWidth &&
			y > Walls[i].y * Walls[i].TextureWidth) ||

			(x + width * cos(angle * PI / 180) < (Walls[i].x + Walls[i].width) * Walls[i].TextureWidth &&
			x + width * cos(angle * PI / 180) > Walls[i].x * Walls[i].TextureWidth &&
			y < (Walls[i].y + Walls[i].height) * Walls[i].TextureWidth &&
			y > Walls[i].y * Walls[i].TextureWidth) ||

			(x < (Walls[i].x + Walls[i].width) * Walls[i].TextureWidth &&
			x > Walls[i].x * Walls[i].TextureWidth &&
			y + height * sin(angle * PI / 180) < (Walls[i].y + Walls[i].height) * Walls[i].TextureWidth &&
			y + height * sin(angle * PI / 180) > Walls[i].y * Walls[i].TextureWidth) ||

			(x + width * cos(angle * PI / 180) < (Walls[i].x + Walls[i].width) * Walls[i].TextureWidth &&
			x + width * cos(angle * PI / 180) > Walls[i].x * Walls[i].TextureWidth &&
			y + height * sin(angle * PI / 180) < (Walls[i].y + Walls[i].height) * Walls[i].TextureWidth &&
			y + height * sin(angle * PI / 180) > Walls[i].y * Walls[i].TextureWidth)
			)

		{
			ok = true;
			break;
		}*/

	if (x < -w/2 + px + 32 || x > w/2 + px + 32 ||
		y < -h/2 + py + 32 || y > h/2 + py + 32 || ok)
		return 1;

	return 0;
}

Bullet::Bullet(int xx, int yy, int aangle)
{
	x = xx;
	y = yy;
	angle = aangle;
	width = 40;
	height = 13;
	speed = 20;
}
