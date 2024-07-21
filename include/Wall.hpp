#pragma once
#include <SFML\Graphics.hpp>

class Wall {
private:

public:
	float x, y,
		width, height;

	int TextureWidth=64;
	int TextureHeight=64;

	sf::Texture texture;

	sf::Sprite sprite;

};