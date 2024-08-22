#include "Gun.hpp"

void Gun::Start()
{
	maxDelayBullet = .2;
	damage = 1;
	pierce = 1;
}

void Gun::HandleAngle(float x, float y, int width, int height,
	double angle)
{
	if (angle > 90 && angle < 270)
		sprite.setScale(1.f, -1.f);
	else
		sprite.setScale(1.f, 1.f);

	sprite.setRotation(angle);
	std::pair<double, double> newPos = calculatePointInDirection(
		x + width / 2, y + width / 2, angle, width / 2);
	sprite.setPosition(newPos.first, newPos.second);
}

void Gun::Shoot(std::vector<Bullet> &Bullets, sf::Texture& Texture,
	float x, float y, float angle)
{
	Bullet newBullet(x, y, angle, damage, pierce);

	int i = Bullets.size();
	Bullets.push_back(newBullet);
	//Bullets[i].sprite.setOrigin(sf::Vector2f(Bullets[i].width/2, Bullets[i].height/2));
	Bullets[i].sprite.setRotation(angle);
	Bullets[i].sprite.setTexture(Texture);
	Bullets[i].sprite.setPosition(Bullets[i].x, Bullets[i].y);
}
