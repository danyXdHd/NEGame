#include "Gun.hpp"

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
