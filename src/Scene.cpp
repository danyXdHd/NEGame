#include "Scene.hpp"
#define _CRT_SECURE_NO_WARNINGS

Scene::Scene()
{
}

void Scene::Start(std::string name)
{
    sceneName = "json\\" + name + ".json";

    Walls.clear();
    EnemySAreas.clear();
    LootSAreas.clear();
    Doors.clear();

    FILE* file;
    errno_t err = fopen_s(&file, sceneName.c_str(), "r");

    std::string json;
    char buffer[256];
    while (fgets(buffer, 256, file) != NULL) {
        json += buffer;
    }

    fclose(file);

    Layout.Parse(json.c_str());

    //==============================Walls====================================
    const rapidjson::Value& wallsArray = Layout["walls"];
    for (rapidjson::SizeType i = 0; i < wallsArray.Size(); ++i) {
        const rapidjson::Value& wall = wallsArray[i];
        if (!wall.HasMember("x") || !wall.HasMember("y") ||
            !wall.HasMember("width") || !wall.HasMember("height") ||
            !wall["x"].IsInt() || !wall["y"].IsInt() ||
            !wall["width"].IsInt() || !wall["height"].IsInt()) {
            std::cerr << "Invalid wall format in JSON file: " << sceneName.c_str() << std::endl;
        }

        Wall w;

        w.x = wall["x"].GetInt();
        w.y = wall["y"].GetInt();
        w.width = wall["width"].GetInt();
        w.height = wall["height"].GetInt();

        if (!w.texture.loadFromFile("Assets\\Images\\Tile.png"))
        {
            std::cout << "Wall nuber: " << i << "`s texture not rendered ";
        }

        Walls.push_back(w);

        Walls[i].texture.setRepeated(true);
        Walls[i].sprite.setTextureRect(sf::IntRect(0, 0, 64 * w.width, 64 * w.height));
        Walls[i].sprite.setPosition(sf::Vector2f(w.x * 64, w.y * 64));
        Walls[i].sprite.setSize(sf::Vector2f(w.width * 64, w.height * 64));
        Walls[i].sprite.setTexture(&Walls[i].texture);

    }

    //==============================EnemySAreas==============================
    const rapidjson::Value& enemyArray = Layout["enemySpawnAreas"];
    for (rapidjson::SizeType i = 0; i < enemyArray.Size(); ++i) {
        const rapidjson::Value& enemyS = enemyArray[i];
        if (!enemyS.HasMember("x") || !enemyS.HasMember("y") ||
            !enemyS.HasMember("width") || !enemyS.HasMember("height") ||
            !enemyS["x"].IsInt() || !enemyS["y"].IsInt() ||
            !enemyS["width"].IsInt() || !enemyS["height"].IsInt()) {
            std::cerr << "Invalid enemy spawn area format in JSON file: " << sceneName.c_str() << std::endl;
        }

        Wall w;

        w.x = enemyS["x"].GetInt();
        w.y = enemyS["y"].GetInt();
        w.width = enemyS["width"].GetInt();
        w.height = enemyS["height"].GetInt();

        EnemySAreas.push_back(w);
    }

    //==============================LootSAreas===============================
    const rapidjson::Value& lootArray = Layout["lootSpawnAreas"];
    for (rapidjson::SizeType i = 0; i < lootArray.Size(); ++i) {
        const rapidjson::Value& lootS = lootArray[i];
        if (!lootS.HasMember("x") || !lootS.HasMember("y") ||
            !lootS.HasMember("width") || !lootS.HasMember("height") ||
            !lootS["x"].IsInt() || !lootS["y"].IsInt() ||
            !lootS["width"].IsInt() || !lootS["height"].IsInt()) {
            std::cerr << "Invalid loot spawn area format in JSON file: " << sceneName.c_str() << std::endl;
        }

        Wall w;

        w.x = lootS["x"].GetInt();
        w.y = lootS["y"].GetInt();
        w.width = lootS["width"].GetInt();
        w.height = lootS["height"].GetInt();

        LootSAreas.push_back(w);
    }

    //==============================Doors====================================
    const rapidjson::Value& doorsArray = Layout["doors"];
    for (rapidjson::SizeType i = 0; i < doorsArray.Size(); ++i) {
        const rapidjson::Value& door = doorsArray[i];
        if (!door.HasMember("x") || !door.HasMember("y") ||
            !door.HasMember("width") || !door.HasMember("height") ||
            !door["x"].IsInt() || !door["y"].IsInt() ||
            !door["width"].IsInt() || !door["height"].IsInt() ||
            !door["doorLocation"].IsInt()
        ) {
            std::cerr << "Invalid door format in JSON file: " << sceneName.c_str() << std::endl;
        }

        Wall w;

        w.x = door["x"].GetInt();
        w.y = door["y"].GetInt();
        w.width = door["width"].GetInt();
        w.height = door["height"].GetInt();

        /*if (!w.texture.loadFromFile("Assets\\Images\\Tile.png"))
        {
            std::cout << "Door nuber: " << i << "`s texture not rendered ";
        }*/

        Doors.push_back(std::make_pair(w, door["doorLocation"].GetInt()));

        Doors[Doors.size()-1].first.sprite.setPosition(sf::Vector2f(w.x * 64, w.y * 64));
        Doors[Doors.size() - 1].first.sprite.setSize(sf::Vector2f(w.width * 64, w.height * 64));
        Doors[Doors.size() - 1].first.sprite.setFillColor(sf::Color(15, 15, 15));
    }

    for (int i = 0; i < Walls.size(); i++) {
        Walls[i].sprite.setTexture(&Walls[i].texture);
    }
}

bool Scene::Update(sf::RenderWindow& Window,
    float& x, float& y, int& width, int& height)
{
    bool loadNextScene = false;

    for (int i = 0; i < Walls.size(); i++) {
        Window.draw(Walls[i].sprite);
    }
    for (int i = 0; i < Doors.size(); i++) {
        if (Doors[i].first.isColiding(x, y, width, height)) {
            loadNextScene = true;
        }

        Window.draw(Doors[i].first.sprite);
    }

    return loadNextScene;
}