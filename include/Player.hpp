#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Gun.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"

class Player
{
private:
	sf::Texture texture;
	sf::Texture gunTexture;
	sf::Texture bulletTexture;

	int speed;
	int maxBullets;
	float delayBullet;

	Gun Gun;

	void LoadTextures();

	void HandleMovement(std::vector<Wall>& Walls, float dTime);

	void HandleBullets(sf::RenderWindow& Window, 
		int width, int height, float dTime, 
		std::vector<Wall>& Walls);

	void HandleGun(sf::RenderWindow& Window);

	void HandleDamage(std::vector<Enemy> &Enemys);

public:
	sf::Sprite sprite;

	int width;
	int height;
	float x, y;
	
	int hp;

	std::vector<Bullet> Bullets;

	void Start();

	void Update(sf::RenderWindow &Window, sf::View &View, 
		int width, int height, float dTime, 
		std::vector<Wall>& Walls, std::vector<Enemy> &Enemys);
};