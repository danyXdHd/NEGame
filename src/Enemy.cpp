#include "Enemy.hpp"

void Enemy::Start(float ex, float ey)
{
	hp = 3;
	speed = 64 * 4;
	x = ex;
	y = ey;
	width = 64;
	height = 64;
	TargetingDist = 5;
	//IFrame = imune frame measured in seconds, NOT IN FRAMES
	// u idiot
	maxIFrame = .2;
	maxShootDelay = .75;

	Gun.Start();
}

void Enemy::Update(sf::RenderWindow &Window, std::vector<Wall>& walls,
	float& px, float& py, int& pwidth, int& pheight, float dTime,
	sf::Texture& bulletTexture)
{
	HandleMovement(walls, px, py, pwidth, pheight, dTime);

	HandleGun(px, py, pwidth, pheight, bulletTexture, dTime);

	HandleBullets(Window, dTime, walls);

	if (iFrame > 0)
		iFrame -= dTime;

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

void Enemy::HandleGun(float& px, float& py, int& pw, int& ph,
	sf::Texture& bulletTexture, float dTime)
{
	Gun.HandleAngle(x, y, width, height, angleWithXAxis(
		x + width / 2, y + width / 2, px + pw/2, py + ph/2));

	if (pow(px - x, 2) + pow(py - y, 2) <= 
		pow(64 * TargetingDist, 2)) 
	{
		if (ShootDelay > 0)
			ShootDelay -= dTime;
		else
		{
			Gun.Shoot(Bullets, bulletTexture, Gun.sprite.getPosition().x,
				Gun.sprite.getPosition().y, Gun.sprite.getRotation());
			
			ShootDelay = maxShootDelay;
		}
	}
	else
		ShootDelay = maxShootDelay;
}

bool Enemy::isColiding(int xx, int yy, int ww, int hh)
{
	return (x < xx + ww &&
		x + width> xx &&
		y < yy + hh &&
		y + height > yy);
}

void Enemy::HandleBullets(sf::RenderWindow& Window, 
	float dTime, std::vector<Wall>& Walls)
{
	for (int i = 0; i < Bullets.size(); i++) {
		Window.draw(Bullets[i].sprite);
		if (Bullets[i].Update(x, y, 50*64, 50*64, dTime, Walls))
			Bullets.erase(Bullets.begin() + i);
	}
}
