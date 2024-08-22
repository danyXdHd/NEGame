#include "Scene.hpp"
#define _CRT_SECURE_NO_WARNINGS

void Scene::LoadTexture()
{
    if (!enemyTexture.loadFromFile("Assets\\Images\\Enemy.png"))
    {
        std::cout << "Enemy texture not rendered";
    }
    if (!gunTexture.loadFromFile("Assets\\Images\\Gun.png"))
    {
        std::cout << "Gun texture not rendered";
    }
    if (!bulletTexture.loadFromFile("Assets\\Images\\Bullet.png"))
    {
        std::cout << "Bullet texture not rendered";
    }
}

Scene::Scene()
{
}

void Scene::Start(std::string name)
{
    LoadTexture();

    sceneName = "json\\" + name + ".json";

    Walls.clear();
    EnemySAreas.clear();
    LootSAreas.clear();
    Doors.clear();
    Enemys.clear();

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

        Door w;

        w.x = door["x"].GetInt();
        w.y = door["y"].GetInt();
        w.width = door["width"].GetInt();
        w.height = door["height"].GetInt();

        /*if (!w.texture.loadFromFile("Assets\\Images\\Tile.png"))
        {
            std::cout << "Door nuber: " << i << "`s texture not rendered ";
        }*/

        Doors.push_back(w);

        Doors[Doors.size()-1].sprite.setPosition(sf::Vector2f(w.x * 64, w.y * 64));
        Doors[Doors.size() - 1].sprite.setSize(sf::Vector2f(w.width * 64, w.height * 64));
        Doors[Doors.size() - 1].sprite.setFillColor(sf::Color(15, 15, 15));
    }

    for (int i = 0; i < Walls.size(); i++) {
        Walls[i].sprite.setTexture(&Walls[i].texture);
    }
}

bool Scene::Update(sf::RenderWindow& Window,
    float& x, float& y, int& width, int& height, float dTime)
{
    // x,y,width,height is from the player
    bool loadNextScene = false;

    if (count >= 60 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        SpawnEnemy(0,0);
        count = 0;
    }
    count++;

    for (int i = 0; i < Walls.size(); i++) {
        Window.draw(Walls[i].sprite);
    }
    for (int i = 0; i < Doors.size(); i++) {
        if (Doors[i].isColiding(x, y, width, height)) {
            loadNextScene = true;
        }
        Window.draw(Doors[i].sprite);
    }
    for (int i = 0; i < Enemys.size(); i++) {
        Enemys[i].Update(Window, Walls, x, y, width, height, dTime, bulletTexture);
        Window.draw(Enemys[i].sprite);
        Window.draw(Enemys[i].Gun.sprite);
    }

    return loadNextScene;
}

void Scene::SpawnEnemy(float ex, float ey)
{
    Enemy e;
    int i = Enemys.size();
    Enemys.push_back(e);
    Enemys[i].Start(ex, ey);
    Enemys[i].sprite.setTexture(enemyTexture);
    Enemys[i].sprite.setPosition(ex, ey);
    Enemys[i].Gun.sprite.setTexture(gunTexture);
}
