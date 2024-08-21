#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Bullet.hpp"

class Gun
{
private:

public:
	float maxDelayBullet = .2;
	float damage = 1;
	int pierce = 1;

	sf::Sprite sprite;

	virtual void Shoot(std::vector<Bullet> &Bullets,sf::Texture &Texture, float x, float y, float angle);
};

