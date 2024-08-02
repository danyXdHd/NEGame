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

	int Count=0;
	sf::Clock clock;
	sf::Time deltaTime;
	double s = 0;


public:
	Application(int value);

	int Start();

	void Update();

	void ChangeScene(std::string name);

};