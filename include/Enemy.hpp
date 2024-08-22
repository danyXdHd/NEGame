#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "SFML/Graphics.hpp"
#include "Gun.hpp"

class Enemy
{
private:
	float speed;
	float TargetingDist;
	float ShootDelay = 0;
	float maxShootDelay;

	std::vector<Bullet> Bullets;

	void LoadTextures();

	void HandleMovement(std::vector<Wall>& Walls,
		float& px, float& py, int& pwidth, int& pheight,
		float dTime);

	void HandleGun(float& px, float& py, int& pw, int& ph,
		sf::Texture& bulletTexture, float dTime);

	void HandleBullets(sf::RenderWindow& Window, float dTime,
		std::vector<Wall>& Walls);

public:
	float x = 0, y = 0;
	float width, height;

	int hp;
	float iFrame;
	float maxIFrame;

	Gun Gun;

	sf::Sprite sprite;

	virtual void Start(float ex, float ey);

	virtual void Update(sf::RenderWindow &Window ,std::vector<Wall>& walls, 
		float& px, float& py, int& pwidth, int& pheight, float dTime,
		sf::Texture &bulletTexture);

	virtual bool isColiding(int xx, int yy, int ww, int hh);

};

