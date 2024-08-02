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

	bool isColiding(int xx, int yy, int ww, int hh) const;
};