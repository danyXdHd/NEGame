#pragma once
#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <Scene.hpp>

class Application
{
private:

	sf::RenderWindow Window;

	sf::View View;

	Player Player;

	Scene Scene;

	int height, width;

public:
	Application(int value);

	int Start();

	void Update();

};