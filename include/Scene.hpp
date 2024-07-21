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

	void Start();

	void Update(sf::RenderWindow& Window);

	void ChangeScene(std::string newSceneName);
	
};