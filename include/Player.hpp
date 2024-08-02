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

	int speed;
	int maxBullets;
	float delayBullet;
	float maxDelayBullet;


	void LoadTextures();

	void HandleMovement(std::vector<Wall>& Walls, float dTime);

	void HandleBullets(sf::RenderWindow& Window, 
		int width, int height, float dTime, 
		std::vector<Wall>& Walls);

	void HandleGun(sf::RenderWindow& Window);


public:
	sf::Sprite sprite;

	sf::Sprite gunSprite;

	double gunAngle;

	int width;
	int height;
	float x, y;

	std::vector<Bullet> Bullets;

	void Start();

	void Update(sf::RenderWindow &Window, sf::View View, 
		int width, int height, float dTime, 
		std::vector<Wall>& Walls);
};