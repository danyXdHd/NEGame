#include "Scene.hpp"
#define _CRT_SECURE_NO_WARNINGS

Scene::Scene()
{
}

void Scene::Start()
{
    sceneName = "json\\Scene1.json";

    FILE* file;
    errno_t err = fopen_s(&file, sceneName.c_str(), "r");

    std::string json;
    char buffer[256];
    while (fgets(buffer, 256, file) != NULL) {
        json += buffer;
    }

    fclose(file);

    Layout.Parse(json.c_str());

    const rapidjson::Value& wallsJson = Layout["walls"];

    /*for (rapidjson::Value::ConstMemberIterator itr = wallsJson.MemberBegin(); itr != wallsJson.MemberEnd(); itr++) {
        const rapidjson::Value& wall = itr->value;

        int i = Walls.size();

        Wall newWall;

        Walls.push_back(newWall);

        Walls[i].TextureWidth = 64;
        Walls[i].TextureHeight = 64;
        Walls[i].x = wall["x"].GetFloat();
        Walls[i].y = wall["y"].GetFloat();
        Walls[i].width = wall["width"].GetInt();
        Walls[i].height = wall["height"].GetInt();

        std::string textureName = "Assets\\Images\\";
        textureName.append(wall["texture"].GetString());


        if (!Walls[i].texture.loadFromFile(textureName.c_str()))
        {
            std::cout << "Wall nuber: " << i << "`s texture not rendered " << textureName;
        }

        Walls[i].texture.setRepeated(true);

        Walls[i].sprite.setTexture(Walls[i].texture);
        Walls[i].sprite.setTextureRect(sf::IntRect(0, 0, 64 * Walls[i].width, 64 * Walls[i].height));

        Walls[i].sprite.setPosition(sf::Vector2f(Walls[i].x * 64, Walls[i].y * 64));
    }*/
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
        w.texture.setRepeated(true);
        w.sprite.setTextureRect(sf::IntRect(0, 0, 64 * w.width, 64 * w.height));
        w.sprite.setPosition(sf::Vector2f(w.x * 64, w.y * 64));

        w.sprite.setTexture(w.texture); 

        Walls.push_back(w);
    }


    for (int i = 0; i < Walls.size(); i++) {
        Walls[i].sprite.setTexture(Walls[i].texture); 
        Walls[i].sprite.setColor(sf::Color::Red);

    }
}

void Scene::Update(sf::RenderWindow& Window)
{
    for (int i = 0; i < Walls.size(); i++) {
        //Walls[i].sprite.setTexture(Walls[i].texture);
        Window.draw(Walls[i].sprite);
    }
}

void Scene::ChangeScene(std::string newSceneName)
{
    sceneName = newSceneName;
}
