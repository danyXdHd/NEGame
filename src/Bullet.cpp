#include "Bullet.hpp"

Bullet::Bullet(int xx, int yy, float aangle, int dmg, int prc)
{
	const double PI = 3.14159265358979323846;
	x = xx;
	y = yy;
	width = 38;
	height = 15;
	speed = 64 * 14;
	angle = aangle;

	damage = dmg;
	pierce = prc;

	std::pair<double, double> newPos = calculatePointInDirection(x, y, angle, speed);
	dx = newPos.first - x;
	dy = newPos.second - y;

	sinc = sin(angle / 180 * PI);
	cosc = cos(angle / 180 * PI);

	WTF0.setFillColor(sf::Color::Transparent);
	WTF0.setOutlineColor(sf::Color::Black);
	WTF0.setOutlineThickness(3);
	WTF0.setSize(sf::Vector2f(4,4));

	WTF1.setFillColor(sf::Color::Transparent);
	WTF1.setOutlineColor(sf::Color::Magenta);
	WTF1.setOutlineThickness(3);
	WTF1.setSize(sf::Vector2f(4, 4));

	WTF2.setFillColor(sf::Color::Transparent);
	WTF2.setOutlineColor(sf::Color::Magenta);
	WTF2.setOutlineThickness(3);
	WTF2.setSize(sf::Vector2f(4, 4));

	WTF3.setFillColor(sf::Color::Transparent);
	WTF3.setOutlineColor(sf::Color::Magenta);
	WTF3.setOutlineThickness(3);
	WTF3.setSize(sf::Vector2f(4, 4));
}


bool Bullet::Update(int px, int py, int w, int h, float dTime, std::vector<Wall>& Walls)
{
	x += dx * dTime;
	y += dy * dTime;
	
	bool ok = false;

	for (int i = 0; i < Walls.size(); i++)
		if ((x < (Walls[i].x + Walls[i].width) * Walls[i].TextureWidth &&
			 x >  Walls[i].x * Walls[i].TextureWidth &&
			 y < (Walls[i].y + Walls[i].height) * Walls[i].TextureWidth &&
			 y >  Walls[i].y * Walls[i].TextureWidth) ||

			(x + width * cosc < (Walls[i].x + Walls[i].width) * Walls[i].TextureWidth &&
			 x + width * cosc >  Walls[i].x * Walls[i].TextureWidth &&
			 y + width * sinc < (Walls[i].y + Walls[i].height) * Walls[i].TextureWidth &&
			 y + width * sinc >  Walls[i].y * Walls[i].TextureWidth) ||

			(x - height * sinc < (Walls[i].x + Walls[i].width) * Walls[i].TextureWidth &&
			 x - height * sinc >  Walls[i].x * Walls[i].TextureWidth &&
			 y + height * cosc < (Walls[i].y + Walls[i].height) * Walls[i].TextureWidth &&
			 y + height * cosc >  Walls[i].y * Walls[i].TextureWidth) ||

			(x + width * cosc - height * sinc < (Walls[i].x + Walls[i].width) * Walls[i].TextureWidth &&
			 x + width * cosc - height * sinc >  Walls[i].x * Walls[i].TextureWidth &&
			 y + width * sinc + height * cosc < (Walls[i].y + Walls[i].height) * Walls[i].TextureWidth &&
			 y + width * sinc + height * cosc >  Walls[i].y * Walls[i].TextureWidth)
			)

		{
			ok = true;
			break;
		}

	sprite.setPosition(x, y);
	WTF0.setPosition(x - 2, y - 2);

	WTF1.setPosition(x - 2 + width*cosc,
					 y - 2 + width*sinc);

	WTF2.setPosition(x - 2 - height*sinc, y - 2 + height*cosc);


	WTF3.setPosition(x - 2 + width * cosc - height * sinc, 
					 y - 2 + width * sinc + height * cosc);

	return (x < -w / 2 + px + 32 || x > w / 2 + px + 32 ||
			y < -h / 2 + py + 32 || y > h / 2 + py + 32 || ok);
}

bool Bullet::isColiding(int xx, int yy, int ww, int hh) const
{
	return ((x < xx + ww  &&
			x >  xx  &&
			y < yy + hh  &&
			y >  yy) || 
			
			(x + width * cosc < xx + ww &&
			x + width * cosc > xx &&
			y + width * sinc < yy + hh &&
			y + width * sinc >  yy) ||

			(x - height * sinc < xx + ww &&
			x - height * sinc >  xx &&
			y + height * cosc < yy + hh &&
			y + height * cosc >  yy) ||

			(x + width * cosc - height * sinc < xx + ww &&
			x + width * cosc - height * sinc >  xx &&
			y + width * sinc + height * cosc < yy + hh &&
			y + width * sinc + height * cosc >  yy)
		);
}

