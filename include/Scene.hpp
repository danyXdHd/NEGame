#pragma once
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <Wall.hpp>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <String>


using namespace rapidjson;

class Scene {
private:
	Document Layout;

public:
	Scene();

	std::string sceneName;

	std::vector<Wall> Walls;

	std::vector<Wall> EnemySAreas;

	std::vector<Wall> LootSAreas;

	std::vector<std::pair<Wall, int>> Doors;

	void Start(std::string name);
	void Update(sf::RenderWindow& Window);
	
};