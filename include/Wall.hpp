#pragma once
#include <SFML\Graphics.hpp>

class Wall {
private:

public:
	int x, y;
	int width, height;
	int TextureWidth=64;
	int TextureHeight=64;

	sf::Texture texture;
	sf::RectangleShape sprite;

	~Wall();

	bool isColiding(int xx, int yy, int ww, int hh) const;
};

class Door : public Wall
{
public:
	int direction;
	/*
		  1
		4   2
		  3
		E.X.: direction == 1 = Nord
		      direction == 2 = West
		      direction == 3 = South
		      direction == 4 = Est
				
	*/
private:
};

class EnemySpawnArea : public Wall
{
public:
private:
};

class LootSpawnArea : public Wall
{
public:
private:
};
