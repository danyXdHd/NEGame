#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Bullet.hpp"
#include <vector>
#include <cmath>

class Enemy
{
private:
	float speed;
	float TargetingDist;

	std::vector<Bullet> bullets;

	void LoadTextures();

	void HandleMovement(std::vector<Wall>& Walls,
		float& px, float& py, int& pwidth, int& pheight,
		float dTime);

	void HandleBullets(sf::RenderWindow& Window,
		int width, int height, float dTime,
		std::vector<Wall>& Walls);

public:
	float x = 0, y = 0;
	float width, height;

	sf::Sprite sprite;

	virtual void Start(float ex, float ey);

	virtual void Update(std::vector<Wall>& walls, 
		float& px, float& py, int& pwidth, int& pheight, float dTime);



};

