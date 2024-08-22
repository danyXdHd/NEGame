#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Bullet.hpp"
#include "Utility.hpp"

class Gun
{
private:

public:
	float maxDelayBullet;
	float damage;
	int pierce;

	sf::Sprite sprite;

	virtual void Start();

	void HandleAngle(float x, float y, int width, int height, double angle);

	virtual void Shoot(std::vector<Bullet> &Bullets,sf::Texture &Texture, float x, float y, float angle);
};

