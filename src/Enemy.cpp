#include "Enemy.hpp"

void Enemy::Start(float ex, float ey)
{
	hp = 3;
	speed = 64 * 4;
	x = ex;
	y = ey;
	width = 64;
	height = 64;
	TargetingDist = 3;
}

void Enemy::Update(std::vector<Wall>& walls,
	float& px, float& py, int& pwidth, int& pheight, float dTime)
{
	HandleMovement(walls, px, py, pwidth, pheight, dTime);

}

void Enemy::LoadTextures()
{
}

void Enemy::HandleMovement(std::vector<Wall>& Walls, 
	float& px, float& py, int& pwidth, int& pheight, float dTime)
{
	if (pow(px-x,2) + 
		pow(py-y,2) > pow(64 * TargetingDist,2))  
	{
		//Warning! Black Magic Incoming!!! 
		float xFactor = abs(px - x) / (abs(px - x) + abs(py - y));
		float yFactor = abs(py - y) / (abs(px - x) + abs(py - y));
		//Has It That Bad? Maybe... I Dunno.

		if (px > x - TargetingDist / 2)
			x += speed * dTime * xFactor;
		if (px < x + TargetingDist / 2)
			x -= speed * dTime * xFactor;

		if (py > y - TargetingDist / 2)
			y += speed * dTime * yFactor;
		if (py < y + TargetingDist / 2)
			y -= speed * dTime * yFactor;

		sprite.setPosition(x, y);
	}
}

bool Enemy::isColiding(int xx, int yy, int ww, int hh)
{
	return (x < xx + ww &&
		x + width> xx &&
		y < yy + hh &&
		y + height > yy);
}

void Enemy::HandleBullets(sf::RenderWindow& Window, int width, int height, float dTime, std::vector<Wall>& Walls)
{
}
