#pragma once
#include <Bullet.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Wall.hpp>
#include <vector>

class Player
{
private:
	sf::Texture texture;
	sf::Texture gunTexture;
	sf::Texture bulletTexture;

	int width;
	int height;
	int speed;
	int maxBullets;
	int delayBullet;
	int maxDelayBullet;

	void LoadTextures();

	void HandleMovement(std::vector<Wall> Walls);

	void HandleBullets(sf::RenderWindow& Window, int width, int height, std::vector<Wall> Walls);

	void HandleGun(sf::RenderWindow& Window);


public:
	sf::Sprite sprite;

	sf::Sprite gunSprite;

	double gunAngle;

	int x, y;

	std::vector<Bullet> Bullets;

	sf::Sprite bulletSprite;

	void Start();

	void Update(sf::RenderWindow &Window, sf::View View, 
		int width, int height, std::vector<Wall> Walls);
};