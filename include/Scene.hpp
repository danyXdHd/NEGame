#pragma once
#include <iostream>
#include <String>
#include "SFML\Graphics.hpp"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "Wall.hpp"
#include "Enemy.h"


using namespace rapidjson;

class Scene {
private:
	Document Layout;

	int count = 0;

	void LoadTexture();

	sf::Texture enemyTexture;
	sf::Texture gunTexture;
	sf::Texture bulletTexture;

public:
	Scene();

	std::string sceneName;

	std::vector<Wall> Walls;

	std::vector<Wall> EnemySAreas;

	std::vector<Wall> LootSAreas;

	std::vector<Door> Doors;

	std::vector<Enemy> Enemys;

	void Start(std::string name);
	bool Update(sf::RenderWindow& Window,
		float& x, float& y, int& width, int& height, float dTime);
	
	void SpawnEnemy(float ex, float ey);

};